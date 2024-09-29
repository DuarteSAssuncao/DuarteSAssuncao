package com.project.l02gr08;

import com.googlecode.lanterna.input.KeyStroke;
import com.project.l02gr08.controller.Controller;
import com.project.l02gr08.controller.MenuController;
import com.project.l02gr08.state.MenuState;
import com.project.l02gr08.state.State;
import com.project.l02gr08.viewer.MenuViewer;
import com.project.l02gr08.viewer.Viewer;

import java.awt.*;
import java.io.IOException;
import java.net.URISyntaxException;

public class Game {
    private State<? extends Controller, ? extends Viewer> state;
    private final GUI gui;

    public Game() throws IOException, FontFormatException, URISyntaxException {
        this.gui = new GUI();
        this.state = new MenuState(new MenuController(), new MenuViewer());
    }

    public Game(State<? extends Controller, ? extends Viewer> state, GUI gui) {
        this.state = state;
        this.gui = gui;
    }

    public static void main(String[] args) 
            throws IOException, FontFormatException, URISyntaxException {
        new Game().start();
    }

    public void setState(State<? extends Controller, ? extends Viewer> state) {
        this.state = state;
    }

    public State<? extends Controller, ? extends Viewer> getState() {
        return this.state;
    }

    public GUI getGUI() {
        return gui;
    }

    public void start() throws IOException {
        do {
            state.getViewer().draw(this);
            KeyStroke key = gui.getScreen().readInput();
            state.getController().step(key, this);
        } while (this.state != null);
        gui.getScreen().close();
    }
}
