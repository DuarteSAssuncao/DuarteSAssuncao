package com.project.l02gr08.state.gamestate;

import com.project.l02gr08.controller.gamecontroller.ChoiceController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.viewer.gameviewer.ChoiceViewer;

public class ChoiceState extends GameState<ChoiceController, ChoiceViewer> {
    public ChoiceState(ChoiceController c, ChoiceViewer v) {
        super(c, v);
    }

    public ChoiceState(ChoiceController c, ChoiceViewer v, Board b) {
        super(c, v, b);
    }
}
