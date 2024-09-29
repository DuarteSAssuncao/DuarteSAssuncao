package com.project.l02gr08.viewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.EndState;
import java.io.IOException;

public class EndViewer implements Viewer {
    @Override
    public void draw(Game game) throws IOException {
        EndState state = (EndState) game.getState();

        GUI gui = game.getGUI();
        Screen screen = gui.getScreen();
        TextGraphics graphics = screen.newTextGraphics();

        screen.clear();

        graphics.setBackgroundColor(new TextColor.RGB(0, 0, 0));
        graphics.setForegroundColor(new TextColor.RGB(200, 200, 200));

        TerminalSize terminalSize = screen.getTerminalSize();
        int width = terminalSize.getColumns();
        int height = terminalSize.getRows();

        graphics.fillRectangle(new TerminalPosition(0, 0), new TerminalSize(width, height), ' ');

        String wins = state.getText().get(0);
        int x = width / 2 - (wins.length() / 2);
        int y = height / 2;
        graphics.putString(new TerminalPosition(x, y), wins);

        String help = state.getText().get(1);
        graphics.putString(new TerminalPosition(0, height - 1), help);

        screen.refresh(Screen.RefreshType.DELTA);
    }
}
