# Documentation pour le Framework MVC H4SH

Le modèle MVC (Model, View, Controller) est une méthode d'organisation des scripts php d'un site web dynamique, il permet de les isoler de l'utilisateur pour réduire les risques de failles et de rendre le code plus lisible afin de faciliter le développement communautaire et la réutilisation des fonctions.

Le framework H4SH prend en charge PHP 7.2 et gère les principales fonctions d'accès à la base de données, la SEO du site et la gestion des ressources multimedia.

L'architecture des dossiers est la suivante

- .htaccess (paramètres pour qu'apache redirige proprement les requètes, il n'est pas nécessaire de le modifier sauf besoins spéciaux)
- Core (contient le ''manager.php'' (script principal qui gère les pages comme **monsite.com/inscription** qui appeleront un modèle)
  - controleurs (les contrôleurs gèrent chacun l'affichage d'une page, ils appellent des modèles pour rendre des fonctions disponibles et des vues pour afficher du contenu statique)
  - modeles (les modèles contiennent les fonctions nécessaires à la génération de la page)
  - vues (les vues servent à afficher l'HTML de la page et à appeler les fonctions des modèles)
  - set (ce dossier contient entre autres les paramètres de la **base de données**)
- Webroot
  - css (contient les feuilles de styles globales aux site ou particulières à une page, pour les appeler l'url est /css/fichier.css)
  - img (contient les contenus multimedia, todo: renommer en media ?, pour appeler le contenu, l'url est /img/fichier.jpg)
  - js (contient les scripts js et les libraries détaché.e.s, pour appeler des fichiers l'url sera /js/fichier.js)
  
  Il est généralement admis que les vues commencent par un v_*nom*.php, les contrôleurs par un c_*nom*.php et les n
  
  
  Site::Url
  
  
  ## Templates pour intéragir avec la base de données
  
  Par défaut H4SH prend en charge une seule base de données (TODO).
