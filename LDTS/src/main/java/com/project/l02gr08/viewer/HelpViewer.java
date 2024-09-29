package com.project.l02gr08.viewer;

import com.google.common.base.Splitter;
import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.HelpState;

import java.io.IOException;
import java.util.List;

public class HelpViewer implements Viewer {
    @Override
    public void draw(Game game) throws IOException {
        HelpState state = (HelpState) game.getState();
        GUI gui = game.getGUI();
        Screen s = gui.getScreen();
        TextGraphics gwafics = s.newTextGraphics();
        TerminalPosition pos = new TerminalPosition(0, 2);

        s.clear();

        for (int i = 0; i < state.getTitles().size(); i++) {
            pos = drawTitle(state.getTitles().get(i), gwafics, pos.withColumn(2));
            pos = drawContent(state.getContents().get(i), gwafics, pos.withColumn(4));
            pos = pos.withRelativeRow(2);
        }

        pos = pos.withRow(gwafics.getSize().getRows() - 1);
        pos = pos.withColumn(0);
        gwafics.putString(pos, state.getExit());

        s.refresh(Screen.RefreshType.DELTA);

    }

    // =====================================================================

    private TerminalPosition drawTitle(String title, TextGraphics gwafics, TerminalPosition pos) {
        gwafics.setForegroundColor(new TextColor.RGB(0, 0, 0));
        gwafics.setBackgroundColor(new TextColor.RGB(155, 155, 155));
        gwafics.putString(pos, title);

        return pos.withRelativeRow(2);
    }

    private TerminalPosition drawContent(List<String> content, TextGraphics gwafics, TerminalPosition pos) {
        gwafics.setForegroundColor(new TextColor.RGB(155, 155, 155));
        gwafics.setBackgroundColor(new TextColor.RGB(0, 0, 0));

        for (String s : content) {
            for (String word : Splitter.on(' ').split(s)) {
                StringBuilder wordBuilder = new StringBuilder(word);
                wordBuilder.append(" ");
                if ((pos.getColumn() + 1 + wordBuilder.length()) > (gwafics.getSize().getColumns() - 5)) {
                    pos = pos.withRelativeRow(2);
                    pos = pos.withColumn(4);
                }
                gwafics.putString(pos, wordBuilder.toString().toUpperCase());
                pos = pos.withRelativeColumn(wordBuilder.length());
            }

            pos = pos.withRelativeRow(2);
            pos = pos.withColumn(4);
        }

        return pos;
    }
}
