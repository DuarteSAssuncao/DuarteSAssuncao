## Planned Features
> [!NOTE]  
> The original plan for this project was too ambitious.  
> Due to the lack of time, we had to leave some features out of the final project, in favor
> of more polished unit tests and documentation.  
> With that in mind, the following features were planned to be implemented since the intermediate
> delivery, but were left out of the final project:


- **En passant** - If a pawn moves two squares forward, and there is an enemy pawn in a diagonal square
next to it, the enemy pawn can capture the pawn as if it had only moved one square forward.
    > ![image](https://upload.wikimedia.org/wikipedia/commons/a/ae/Ajedrez_captura_al_paso_del_peon.png)  
      Source: https://en.wikipedia.org/wiki/En_passant
  

- **Draw detection** - The game will end automatically if the player is not in check, but there is no
way to move without being in check, or by mutual agreement.


- **Timer for both players** - Each player will have a timer that will count down the time left to
make a move. If the timer reaches zero, the player will lose the game. This clock can be configured
at the start of the game to increment the time left after each move, for example.


- **Score system for both players** - A general score that shown the relative lead of one player over
the other. This score will be calculated based on the value of the pieces that each player has captured.
It does not impact the game, it only is useful as a rough guide to see which player is winning.
    > - **Pawn** - 1 point;
    > - **Rook** - 5 points;
    > - **Knight** - 3 points;
    > - **Bishop** - 3 points;
    > - **Queen** - 9 points.  
    > 
    > See https://en.wikipedia.org/wiki/Chess_piece_relative_value for more information about this system.
