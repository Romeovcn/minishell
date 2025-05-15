# 🐚 minishell

**minishell** est une implémentation simplifiée d'un shell Unix, développée en C. Il permet d'exécuter des commandes, de gérer les redirections, les pipes, et bien plus encore, offrant ainsi une compréhension approfondie du fonctionnement interne d'un shell.

---

## 📋 Fonctionnalités

* Affichage d'un prompt interactif.
* Gestion de l'historique des commandes.
* Exécution de commandes avec recherche dans le `PATH`.
* Gestion des signaux avec une seule variable globale.
* Interprétation correcte des guillemets simples `'` et doubles `"`.
* Implémentation des redirections :

  * `<` : redirection d'entrée.
  * `>` : redirection de sortie.
  * `<<` : here-document.
  * `>>` : redirection de sortie en mode append.
* Gestion des pipes `|` pour enchaîner les commandes.
* Support des variables d'environnement et de leur expansion avec `$`.
* Implémentation des commandes intégrées :

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`

---

## 🛠️ Compilation

Utilisez le `Makefile` fourni pour compiler le projet

```bash
make
```

Cela génèrera l'exécutable `minishell`.

---

## 🚀 Utilisation

Lancez le shell avec :

```bash
./minishell
```

Vous pouvez ensuite entrer des commandes comme dans un shell classique :

```bash
minishell$ ls -la
minishell$ echo "Hello, World!"
minishell$ cat < input.txt | grep "pattern" > output.txt
```

---

## ⚠️ Contraintes

* Respect strict des normes de codage.
* Aucune fuite de mémoire n'est tolérée.
* Utilisation d'une seule variable globale pour la gestion des signaux.
* Gestion appropriée des erreurs et des cas limites.
