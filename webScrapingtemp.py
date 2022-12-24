from cgitb import text
from bs4 import BeautifulSoup

import requests
# Special thanks to Daisy who encourage me to put this onto github.  Daisy you are very kind and you are a very important person to me.

# Main Fetch section
html_text = requests.get('https://www.cars.com/shopping/results/?list_price_max=&makes[]=mercedes_benz&maximum_distance=all&models[]=mercedes_benz-s_class&page=1&page_size=100&stock_type=new&zip=97331').text
soup = BeautifulSoup(html_text, 'lxml')
    # Here you check html and find smallest big tags(div) that contains all your info
all_vehicle_card = soup.find_all('div', class_ = 'vehicle-details')


# Filtering Section
#-Making this to a prompt functin later
print(f'''(Leave blank if not applicable:
Please type in model not wanted:
''')
unwanted_car_make = 'S 580'
print(f'Filtering our {unwanted_car_make}')

# Main logirithm and command
def find_cars():
    
    for ii, car in enumerate(all_vehicle_card):
        car_make = car.find('h2', class_= 'title').text
        primary_price = car.find('span',class_= 'primary-price').text
        dealer_name = car.find(class_ = 'vehicle-dealer').text.replace('\n','')
        
        # Filter section embedded in with Output section
        if unwanted_car_make not in car_make:
            fab = ii*'-'
            
            # Output Section
            with open('cars.txt','a') as f:
                f.write(f"--------{fab}{ii}------\n")
                f.write(f" Make:  {car_make}  \n")
                f.write(f" Price:  {primary_price}  \n")
                f.write(f" Dealer:  {dealer_name}  \n")
            print(f'File saved: {ii}\n\n')

if __name__ == "__main__":
        find_cars()

#I need a good ui
#I need a good way to input parameters with link and car model.
# Optional: I may need to run this periodically

# This program requires 2 libs: BeautufulSoup4 and requests, Please pip -install them before using.
# 
# -William
