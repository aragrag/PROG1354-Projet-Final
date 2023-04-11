
# Introduction : 


L'objectif de ce projet est de créer une station météo en utilisant un microcontrôleur ESP32 et le capteur BME280. J'ai choisi de stocker les données localement sur le microcontrôleur à l'aide de la bibliothèque SPIFFS, et j'ai intégré les bibliothèques AsyncElegantOTA et JSON pour faciliter la mise à jour (OTA) et la transmission des données via le protocole JSON.
<br>
<br>
Dans le but de  rendre les données météorologiques facilement accessibles à tous, où que je sois. C'est pourquoi j'ai créé une page web simple à l'aide de la bibliothèque ESPAsyncWebServer et de la technologie AJAX, qui permet d'afficher les données stockées dans le fichier JSON en temps réel.
<br>
<br>

Dans ce rapport, je vais vous présenter toutes les étapes de création de ma station météo, de la sélection du matériel à la mise en place des bibliothèques AsyncElegantOTA, JSON, et ESPAsyncWebServer. Je vous montrerai également comment j'ai configuré l'environnement de développement, comment j'ai connecté le capteur BME280, et comment j'ai créé la page web à l'aide de Bootstrap  pour afficher les données météorologiques.
<br>
<br>

Enfin, je vous présenterai les résultats obtenus, y compris des captures d'écran de la page web en action, et je vous donnerai des idées pour améliorer encore plus ce projet.


# But de projet : 



Le but de ce projet était de créer une station météo simple et abordable pour surveiller la température, l'humidité et la pression atmosphérique à l'aide d'un capteur I2C (BME280) pour mesurer les données en temps réel. Nous avons choisi d'utiliser le microcontrôleur ESP32 pour sa puissance de traitement, sa connectivité Wi-Fi et sa facilité de programmation. 
<br>
<br>

Enfin, nous avons intégré les bibliothèques AsyncElegantOTA et JSON pour faciliter la mise à jour du micrologiciel et la transmission des données. <br>

L'objectif final était de créer une station météo accessible pour tout le monde, avec un affichage simple des données météorologiques en temps réel sur une page web. Donc pour combiner toute la reconnaissance acquise lors des 2 sessions (OTA, JSON, Bootstrap, WIFI, SPIFFS, WIRE, WebServer, …), dans un seul projet “construction d'une petite station météo”.


# Explications du circuit et diagramme : 

![Shema3 (1)](https://user-images.githubusercontent.com/10962233/231042819-5a80c6c8-3812-4323-9547-fa999ebfdee8.png)


## Pour ce projet, j’ai besoin de : 


- ESP32 
- BME280 sensor module 
- 4 x Câbles 
- Breadboard




# Montage du circuit (réel):

![shema!](https://user-images.githubusercontent.com/10962233/231042870-cf7e4dab-d793-455e-822e-d5499eeedd5a.jpg)

<br>
<br>



# Fonctionnement du code : 
## La structure de mon projet :


![files](https://user-images.githubusercontent.com/10962233/231043016-bb0530e9-9132-456a-b2f6-b1ce322be8f4.png)

### .pio:
C’est un dossier caché créé par la plateforme de développement PlatformIO lors de la compilation et de la construction de votre projet. Il contient plusieurs fichiers et sous-dossiers qui sont utilisés pour stocker des informations et des fichiers temporaires pour votre projet:
build : Contient les fichiers générés lors de la compilation de votre projet. Ces fichiers sont temporaires et sont supprimés lors de la compilation suivante. (spiffs.bin, firmware.bin)
libdeps : Contient les bibliothèques installées pour votre projet, ainsi que les fichiers d'en-tête associés à ces bibliothèques.
environments : Contient des fichiers de configuration pour les différents environnements de développement, tels que les cartes ESP32 et les options de compilation.

### data :
C’est un dossier spécial utilisé dans le contexte de SPIFFS. Ce dossier est utilisé pour stocker les fichiers statiques tels que les fichiers HTML, CSS, JavaScript et autres fichiers nécessaires pour l'interface utilisateur web de votre projet.

### src/main.cpp:
C’est un fichier source qui fait partie du code principal de votre projet ESP32. Ce fichier est généralement responsable de l'initialisation de votre projet et de la configuration des bibliothèques et des composants matériels nécessaires à son fonctionnement.

### platformio.ini :
C’est un fichier de configuration utilisé par la plateforme de développement PlatformIO pour spécifier les paramètres de compilation, les bibliothèques utilisées, les options de téléversement et d'autres paramètres pour votre projet.

<br>
<br>

## Libraries
![Libraries](https://user-images.githubusercontent.com/10962233/231043041-3df8390c-4eb1-49dc-bd88-98e2cd05961c.png)


La bibliothèque Wire pour utiliser I2C.
Les bibliothèques Adafruit_Sensor et Adafruit_BME280 pour interfacer avec le capteur BME280.
La bibliothèque AsyncElegantOTA crée un serveur web auquel vous pouvez accéder sur votre réseau local pour télécharger de nouveaux microprogrammes ou fichiers dans le système de fichiers.
La bibliothèque ArduinoJson moyenne de décoder et d'encoder des chaînes JSON.


<br>
<br>

## Communication I2C
![Communication I2C](https://user-images.githubusercontent.com/10962233/231043053-4c2cf450-a30f-46b0-9ef9-0e7474291a12.png)

Dans ce projet on a utilisé la communication I2C. Il suffit de créer un objet  Adafruit_BME280 appelé bme.



Initialisation du capteur BME ou bien afficher le message "Could not find a valid BME280 sensor, check wiring!" avec une boucle infinie.

Impression des valeurs dans un fichier JSON

Dans la boucle loop(), cette section lit les valeurs du BME280 et imprime les résultats dans le fichier JSON (data.json).



<br>
<br>

## Téléchargement de fichiers à l'aide du Filesystem Uploader SPIFFS.h


![OTA1](https://user-images.githubusercontent.com/10962233/231043487-b492e7ca-954b-4c2d-9ecb-b6aacf37864b.png)

On vérifie que le fichier data.json existe bien dans la mémoire Flash de mon ESP32 Sinon on crée un nouveau tableau JSON.

![SPIFFS1](https://user-images.githubusercontent.com/10962233/231043118-344e737e-337f-4ff1-a1bc-59ddcf0b6c81.png)



Ouvrir le fichier JSON (data.json) en mode lecture-écriture avec un message d'erreur en cas d'échec.

![SPIFFS2](https://user-images.githubusercontent.com/10962233/231043175-4a0b2e2d-1a12-4306-9db8-2fa8fd3ff81b.png)
<br>
<br>

## Mise à jour du nouveau code à l'aide d'OTA
La bibliothèque AsyncElegantOTA crée un serveur web auquel vous pouvez accéder sur votre réseau local pour télécharger de nouveaux microprogrammes ou fichiers dans le système de fichiers (SPIFFS).

![OTA-start](https://user-images.githubusercontent.com/10962233/231043349-3b12d4de-95b1-45d1-b802-05e6ccb84074.png)

![OTA](https://user-images.githubusercontent.com/10962233/231043422-c5ede6c2-164a-4915-a9c1-0cad8cb23db3.png)
<br>
<br>

## Initialisation du Wi-Fi 

![WIFI-Access](https://user-images.githubusercontent.com/10962233/231043196-ff70882b-64c8-4607-9c12-7088f2acee5c.png)



Les identifiants réseau dans les variables suivantes afin que l'ESP32 puisse se connecter à notre réseau local.

![WIFI init](https://user-images.githubusercontent.com/10962233/231043206-30c862e9-1e8e-442c-a793-670ec3a0f5e3.png)

<br>
<br>

## Initialisation Wifi avec les identifiants dessus, et affichage de l'adresse IP de mon ESP32 sur Serial Monitor.

Renvoie la page index.html (AsyncWebServer)

![page-web-handle](https://user-images.githubusercontent.com/10962233/231043650-43c29a6f-3e0f-40ed-8358-56eef9159260.png)


Cette ligne de code sert les fichiers à la racine du serveur web ("/") à partir du système de fichiers SPIFFS (SPIFFS) en utilisant le fichier index.html comme page d'accueil par défaut (setDefaultFile("index.html")).

Cela signifie que lorsque quelqu'un accède à l'adresse IP de votre ESP32, le serveur web renverra le contenu du fichier index.html s'il est disponible. Cela permet de créer une page web simple pour afficher les données météorologiques en temps réel.
<br>
<br>


## Renvoie la page index.html (AsyncWebServer)
![230963841-0cc09077-77ee-4b5f-98c4-8fff30750c2b](https://user-images.githubusercontent.com/10962233/231043673-76381bd4-ee84-43a7-817c-7f8dcf15ceef.png)


Permet de mettre à jour le micrologiciel d'un microcontrôleur ESP32 via une connexion Wi-Fi, sans avoir à le connecter physiquement à un ordinateur ou à un autre périphérique.

Renvoie la page index.html (AsyncWebServer)
Nous devons donc écrire du texte HTML pour construire une page à l'aide de Bootstrap qui fait appel à notre fichier Json (data.json) en utilisant Ajax et jQuery.

On affiche les valeurs dans une page web servie par ESP32.




