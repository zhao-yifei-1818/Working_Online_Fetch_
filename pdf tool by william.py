#!/usr/bin/env python3


        
from PyPDF2 import PdfFileReader, PdfFileWriter
from pathlib import Path
pdf_path = (
     Path.home()
     / "creating-and-modifying-pdfs"
     / "practice_files"
     / "Pride_and_Prejudice.pdf"
 )
input_pdf = PdfFileReader(str(r"C:\Users\Wiliam Fei\Downloads\2.1-247.pdf"))
pdf_reader = PdfFileReader(str(r"C:\Users\Wiliam Fei\Downloads\2.1-247.pdf"))
num_pages = pdf_reader.getNumPages()
pdf_writer = PdfFileWriter()
def check3_2(text):
    with text as f:
        if '3*2' in f.read(text):
            return True
for page in pdf_reader.pages:
    text = page.extractText()
    if check3_2(text):
        page = input_pdf.getPage(n)
        pdf_writer.addPage(page)
with Path("3_2.pdf").open(mode="wb") as output_file:
    pdf_writer.write(output_file)