package com.project.l02gr08.state;

import com.project.l02gr08.controller.EndController;
import com.project.l02gr08.viewer.EndViewer;

import java.util.Arrays;
import java.util.List;

public class EndState extends State<EndController, EndViewer> {
    private final List<String> text;

    public EndState(EndController controller, EndViewer viewer, String winner) {
        super(controller, viewer);
        text = Arrays.asList(winner + " WON!", "PRESS ANY KEY TO GO BACK TO THE MAIN MENU.");
    }

    public List<String> getText() {
        return text;
    }
}
