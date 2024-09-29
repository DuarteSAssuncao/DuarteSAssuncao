package com.project.l02gr08.viewer;

import java.io.IOException;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.Screen.RefreshType;
import com.project.l02gr08.state.MenuState;
import java.util.List;

public class MenuViewer implements Viewer {

    @Override
    public void draw(Game game) throws IOException {
        MenuState state = (MenuState) game.getState();
        GUI gui = game.getGUI();
        Screen s = gui.getScreen();
        TextGraphics gwafics = s.newTextGraphics();
        s.clear();
        TerminalSize xy = s.getTerminalSize();
        int x = xy.getColumns();
        int y = xy.getRows();
        List<String> entries = state.getEntries();
        int selected = state.getSelection();
        String gameName = "Chess";
        gwafics.putString(new TerminalPosition(x/2 - gameName.length() / 2, y / 7), gameName);
        for (int i = 0; i < entries.size(); ++i) {
            int newX = x / 2 - (entries.get(i).length() / 2);
            int newY = y / 3 + i * 2;
            gwafics.setBackgroundColor(new TextColor.RGB(0, 0, 0));
            gwafics.setForegroundColor(new TextColor.RGB(155, 155, 155));
            if (i == selected) {
                gwafics.setForegroundColor(new TextColor.RGB(222, 90, 90));
            }
            gwafics.putString(new TerminalPosition(newX, newY), entries.get(i));
        }
        s.refresh(RefreshType.DELTA);
    }
}
