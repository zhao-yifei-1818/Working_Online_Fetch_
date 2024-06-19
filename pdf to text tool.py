from pathlib import Path
from PyPDF2 import PdfFileReader

# Change the path below to the correct path for your computer.
pdf_path = (
    Path.home()
    / "creating-and-modifying-pdfs"
    / "practice-files"
    / "Pride_and_Prejudice.pdf"
)

# 1
pdf_reader = PdfFileReader(str(r"C:\Users\Wiliam Fei\Downloads\2.1-247.pdf"))
output_file_path = Path.home() / "test1.txt"
search_keywords=['3*2']
# 2
with output_file_path.open(mode="w") as output_file:
    # 3
    title = pdf_reader.documentInfo.title
    num_pages = pdf_reader.getNumPages()
    output_file.write(f"{title}\\nNumber of pages: {num_pages}\\n\\n")

    # 4
    for page in pdf_reader.pages:
        text = page.extractText()
        text=text.split(",")
        
    for sentence in text:
        lst = []
        for word in search_keywords:
            if word in sentence:
                lst.append(word)
        print('{0} key word(s) in sentence: {1}'.format(len(lst), ', '.join(lst)))
        print(sentence + "\n")

    #output_file.write(text)
