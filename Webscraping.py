import re
import requests

# Hämta HTML-filen
response = requests.get("http://example.com")
html = response.text

# Använd en reguljär uttryck för att hitta alla mejladresser
emails = re.findall(r'[\w\.-]+@[\w\.-]+', html)

# Skriv ut alla mejladresser
for email in emails:
    print(email)
