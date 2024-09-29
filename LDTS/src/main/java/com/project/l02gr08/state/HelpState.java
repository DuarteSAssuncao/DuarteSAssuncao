package com.project.l02gr08.state;

import com.project.l02gr08.controller.HelpController;
import com.project.l02gr08.viewer.HelpViewer;

import java.util.List;

public class HelpState extends State<HelpController, HelpViewer> {
    private final List<String> titles = List.of(" HELP ", " CONTROLS ", " MORE INFO ");
    private final List<List<String>> contents = List.of(
            List.of(
                    "Welcome to the game of chess!",
                    "In chess, you have six pieces: the rook, the knight, the bishop, the queen, the king and the pawn.",
                    "Each one has its own types of moves.",
                    "The final goal of the game is to do check mate to the king of the opponent, that is, arranging the pieces in a position that the king is attacked and cannot move anywhere else to escape."),
            List.of(
                    "Use the arrow keys to move the cursor (green box) around the board.",
                    "Press ENTER to select a piece.",
                    "Press ENTER again to select a position to move the piece, or ...",
                    "Press ESC to deselect a piece.",
                    "(The gray boxes are the possible positions to move the selected piece)"),
            List.of(
                    "For more information on the rules of chess, please visit the project's report."));
    private final String exit = "PRESS ESC TO GO BACK TO THE MAIN MENU.";

    public HelpState(HelpController controller, HelpViewer viewer) {
        super(controller, viewer);
    }

    public List<String> getTitles() {
        return titles;
    }

    public List<List<String>> getContents() {
        return contents;
    }

    public String getExit() {
        return exit;
    }
}
