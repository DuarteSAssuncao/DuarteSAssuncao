package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;
import com.project.l02gr08.viewer.MenuViewer;

public class EndController implements Controller {
    @Override
    public void step(KeyStroke key, Game game) {
        MenuState nextState = new MenuState(new MenuController(), new MenuViewer());
        game.setState(nextState);
    }
}
