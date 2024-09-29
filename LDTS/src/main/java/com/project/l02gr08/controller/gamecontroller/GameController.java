package com.project.l02gr08.controller.gamecontroller;

import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.controller.Controller;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.state.gamestate.GameState;
import com.project.l02gr08.viewer.gameviewer.GameViewer;

public interface GameController<T extends GameState<? extends GameController<T>, ? extends GameViewer>>
        extends Controller {

    boolean isValid(KeyType key, T state);

    Position preferredInitialCursor(Board b);
}
