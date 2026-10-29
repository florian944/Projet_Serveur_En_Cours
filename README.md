# Projet_Serveur
Dès le début de mes études supérieur, j'ai eu envie de mettre en place un serveur, cependant, cela n'avais pas pu se réaliser car je n'avais pas le matériel nécessaire. C'est pendant des vacances, je me suis rappelé d'un vieux PC que mon lycée m'avait donné. Je me suis donc servit de ce dernier pour en faire un serveur pour qu'il puisse me permettre de faire mes tests et accueillir des applications. Ce
Pour faire cela, j'ai dû changer l'OS du PC en passant d'un Windows vers un Ubuntu server à l'aide d'une clé USB. Cependant, je me suis rapidement rendu compte que le PC allait rapidement manquer de puissance du coup j'ai choisi d'utiliser Docker au lieu d'un hyperviseur (machine virtuelle).

## Avantages de ce PC
- **Pas de fichier :** je n'ai presque pas utilisé Ce PC donc je ne risque pas de perdre des données
- **OS utilisé :** pour faire ce projet, j'ai utilisé l'OS Ubuntu Server, Cela m'a permit d'avoir un OS gratuit, open source et connue (avec beaucoup de documentation)
- **Portabilité :** c'est un PC portable, si je le veux je peux facilement le déplacer
- **Sur batterie :** c'est un PC portable, il dispose donc d'une batterie
- **Carte wifi intégré :** c'est un PC portable, il dispose donc du wifi, cela peut être utile lors des déplacements

## Inconvénients de ce PC
- **Puissance limité :** peu de puissance, aura peut être besoin d'augmenter la puissance du PC
- **Pas de prise RJ45 :** le PC ne dispose pas de prise RJ45, besoin d'acheter un adaptateur si je veux le passer en filaire
- **Problème de la batterie :** Le PC est tout le temps alimenté par le chargeur, possibilité de problème avec la batterie (à vérifier)
- **Mémoire limité :** mémoire faible, dans le futur il y aura besoin de l'augmenter ou trouver une autre solution

## Topologie du réseau
Le projet serveur état toujour en cours de développement, le schéma ci-dessous représentant la topologie du réseau sera donc amené à évoluer. Cependant, à ce jour, mon réseau est construit sous cette forme.  
<img width="1262" height="542" alt="TopologieRéseau" src="https://github.com/user-attachments/assets/600c26ec-0933-454f-8ace-d0b3d2157230" />
> TopologieRéseau


## Organisation du repository

```text
Projet_Serveur/
└── README.png                           # Image de la topologie du réseau
└── TopologieRéseau.drawio               # Diagramme de la topologie du réseau
└── README.md                            # Documentation du repository
└── Raspberry Pi vers WAN/
    └── PiHole/
        ├── config/
        │   └── apache/                  # Fichiers relié à la création et à la configuration de la page web
        ├── AccueilPiHole.png            # Image de la page d'accueil de PiHole
        └── README.md                    # Documentation du module
    └── VPN - Netbird/
        ├── NetbirdWeb.png               # Image de la page web netbird
        ├── LoginNetbird.png             # Image de login netbird
        └── README.md                    # Documentation du module
└── Navigation et gestion
    └── Nginx/
        ├── config/
        │   └── nginx.conf/              # Fichiers relié à la création et à la configuration de la page web
        └── README.md                    # Documentation du module
    └── Accueil/
        ├── config/
        │   └── web                      # Fichiers relié à la création et à la configuration de la page web
        ├── PageAccueil.png              # Image de la page web d'accueil
        └── README.md                    # Documentation du module
    └── Portainer/
        ├── PagePortainer.png            # Image de la page web de Portainer
        └── README.md                    # Documentation du module
    └── autreAppGestion/
        ├── PagePortainer.png            # Image de la page web de 
        └── README.md                    # Documentation du module
└── Home_Assistant_En_Cours/
    ├── config/
    │   ├── ModèleBoîtier3D/           
    │       └── EntréeX/                 # Fichiers 3D (en .stl avec "X" le numéro du boîtier)
    │   ├── Mosquitto/                   # Fichiers relié à la création et à la configuration de mosquitto
    │   ├── NodeRed/                     # Fichiers relié à la création et à la configuration de NodeRed + Flows et nodes exportés
    │   └── web/                         # Fichiers relié à la création et à la configuration de la/les pages web
    ├── Code ESP entrée/
    │   └── espEntree/                   # Code C++ / Arduino
    ├── Docker/
    │   └── docker-compose.yml           # Lancement des conteneur de ce projet MQTT / Node-RED / Apache
    ├── Schéma réseau IOT.png            # Schéma réseau et architecture
    └── README.md                        # Documentation du module
└── multimédia/
    └── Plex/
        ├── PagePlex.png                 # Image de la page web de Plex
        └── README.md                    # Documentation du module
└── test/
    └── Globe3D/
        ├── config/
        │   └── index.html               # Fichiers relié à la création et à la configuration de la page web
        ├── PageGlobe3D.png              # Image de la page web du globe 3D
        └── README.md                    # Documentation du module
