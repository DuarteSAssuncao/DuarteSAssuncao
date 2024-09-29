# DA2024_PRJ1_G17_5
Repository for the first project of "Desenho de Algoritmos", group 5, class 2LEIC17.
In this project we make an Analysis Tool for Water Supply Management.

This project was developed by:
 - Duarte Assunção - up202208319@up.pt - 33.(3)% effort
 - Lucas Bessa - up202208396@up.pt - 33.(3)% effort
 - Pedro Gorobey - up202210292@up.pt - 33.(3)% effort

---

## How to use
We developed an CLI (Command Line Interface) to allow the user to easily interact with the Network.
The user can, then, type the command associated with the desired functionality, as described below.

### Available Commands
Each command described below has its name on the left, the number of arguments it receives in the middle and which arguments those are on the right.
The description of the command can be found bellow.

    exit:              takes no arguments
        Terminates the program.

    help:              takes no arguments
        Prints this list of commands.

    display_city:      takes 1 argument    display_city <city_id | -all>
        Displays the City with that id, or all of them in case the flag -all is used.

    display_reservoir: takes 1 argument    display_reservoir <reservoir_id | -all>
        Displays the Reservoir with that id, or all of them in case the flag -all is used.

    display_station:   takes 1 argument    display_station <station_id | -all>
        Displays the Pumping Station with that id, or all of them in case the flag -all is used.

    needy_cities:      takes no arguments
        Displays the cities whose water demand is not fulfilled by the network.

    remove:            takes 1 argument    remove <code>
        Removes a City, Reservoir, or a Pumping Station from the network and prints the Cities/Reservoirs affected.
        Do not forget to use the restore command to add the removed location again to the network.

    remove_pipe:       takes 2 arguments   remove_pipe <code_origin> <code_destination>
        Removes a Pipe from the network and prints the Cities/Reservoirs affected.
        Do not forget to use the restore command to add the removed location again to the network.

    restore:           takes no arguments
        Undoes the previous removal. The network will be as in the beginning.

    show_dependency:   takes 1 argument    show_dependency <city_id>
        For a given City, shows which Pipelines, if ruptured, would affect the amount of water reaching the City.

    pipes_statistics:  takes no arguments
        Displays statistics about the flow/capacity ratio of the pipes, like their average ratio, amount of empty/full pipes, etc.