```plain
   ______                    _       ____          __ 
  / ____/_  _____  _________| |     / / /_  ____ _/ /_
 / / __/ / / / _ \/ ___/ ___/ | /| / / __ \/ __ `/ __/
/ /_/ / /_/ /  __(__  |__  )| |/ |/ / / / / /_/ / /_  
\____/\__,_/\___/____/____/ |__/|__/_/ /_/\__,_/\__/  
                                                                                                     
```
### Guess What
#### Overview
This is a interesting game which allows you to answer a few question
and gives you a conjecture through its powerful intelligence and databse.
The more you play this game, the more the AI's accuracy will be improved.
The AI will give you conjectures according to the database and your replies
step by step. In addition, it has the ability of learning. After tell it how
to identify two thing which are similar to each other, the AI will recognize
them accurately. It's sure that this game will bring you a great of fun.

#### Usage
 - This game is a cross-platform program. Without changing source codes and 
 configure files, it can be built in any OS with a `C++` complier.
 - Use `git clone` to clone this repository and run `make` to build this game.
 ```shell
git clone https://github.com/ctj12461/GuessWhat.git
cd GuessWhat/Source
make && make sweep
./GuessWhat
 ```
 - This game need a database to support its running, but it'll generate a
 default one named `DefaultDatabase` in a directory and `GuessWhat.config` 
 by itself. **Don't remove them if you don't know what you're doing.**
 - You can also move another database directory here and change the name in
 `GuessWhat.config` to load it.

#### License
Copyright (C) Justin Chen (aka ctj12461)

The content of this repository is bound by the following licenses:
 - The computer software is licensed under the GNU-LGPL-v3.0 license.
 - The other text resouce is licensed under the CC-BY-SA-4.0 license.

Welcome to make contributions to this project!
