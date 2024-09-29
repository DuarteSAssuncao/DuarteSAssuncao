package com.project.l02gr08.viewer;

import com.project.l02gr08.Game;

import java.io.IOException;

public interface Viewer {
    void draw(Game game) throws IOException;
}
