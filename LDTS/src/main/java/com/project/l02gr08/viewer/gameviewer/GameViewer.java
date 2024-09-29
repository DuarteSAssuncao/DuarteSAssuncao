package com.project.l02gr08.viewer.gameviewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.controller.gamecontroller.GameController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.King;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.model.pieces.Piece.Paint;
import com.project.l02gr08.model.pieces.Piece.Team;
import com.project.l02gr08.state.gamestate.GameState;
import com.project.l02gr08.viewer.Viewer;

public abstract class GameViewer implements Viewer {
    protected final int BLOCK_SIZE = 11;

    public <T extends GameState<? extends GameController<?>, ? extends GameViewer>> void drawBoard(Screen screen,
            T state) {
        Board board = state.getBoard();
        int length = board.getBoardLength();
        int charactersToFill = BLOCK_SIZE;
        TextGraphics gwafics = screen.newTextGraphics();
        int y_coord = 8;
        int x_coord = 0;
        char[] letters = {'a','b','c','d','e','f','g','h'};

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i % 2 == j % 2) {
                    gwafics.setBackgroundColor(new TextColor.RGB(191, 153, 114));
                } else {
                    gwafics.setBackgroundColor(new TextColor.RGB(93, 47, 39));
                }

                gwafics.fillRectangle(
                        new TerminalPosition(i * charactersToFill, j * charactersToFill),
                        new TerminalSize(BLOCK_SIZE, BLOCK_SIZE),
                        ' ');

                if (i == 0) {
                  gwafics.setForegroundColor(
                          j % 2 == 1 ?
                                  new TextColor.RGB(191, 153, 114) :
                                  new TextColor.RGB(93, 47, 39)
                  );
                  gwafics.putString(
                          new TerminalPosition(i, j * charactersToFill + (charactersToFill - 2)),
                          Integer.toString(y_coord));
                  y_coord--;
                }
                if (j == length - 1) {
                  gwafics.setForegroundColor(
                          i % 2 == 0 ?
                                  new TextColor.RGB(191, 153, 114) :
                                  new TextColor.RGB(93, 47, 39)
                  );
                  gwafics.putString(
                          new TerminalPosition(
                                  i * charactersToFill + 1,
                                  j * charactersToFill + charactersToFill - 1
                          ),
                          "" + letters[x_coord]
                  );
                  x_coord++; 
                }
            }
        }
    }

    public <T extends GameState<? extends GameController<?>, ? extends GameViewer>> void drawCursor(Screen screen,
            T state) {
        Position cursor = state.getCursor();
        TextGraphics gwaphics = screen.newTextGraphics();
        gwaphics.setBackgroundColor(new TextColor.RGB(152, 251, 152));
        gwaphics.drawRectangle(new TerminalPosition(cursor.getX() * BLOCK_SIZE, cursor.getY() * BLOCK_SIZE),
                new TerminalSize(BLOCK_SIZE, BLOCK_SIZE), ' ');
    }

    public void drawPiece(Screen screen, Piece piece) {
        Position pos = piece.getPosition();
        int x = pos.getX() * BLOCK_SIZE + 1;
        int y = pos.getY() * BLOCK_SIZE + 1;
        Team color = piece.getTeam();
        Paint[] drawing = piece.getDrawing();
        TextGraphics gwafics = screen.newTextGraphics();
        if (color == Team.BLACK) {
            gwafics.setForegroundColor(new TextColor.RGB(204, 0, 0));
            gwafics.setBackgroundColor(new TextColor.RGB(0, 0, 0));
        } else if (color == Team.WHITE) {
            gwafics.setForegroundColor(new TextColor.RGB(0, 191, 255));
            gwafics.setBackgroundColor(new TextColor.RGB(255, 255, 255));
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (drawing[j * 9 + i] == Paint.Trns) {
                    continue;
                }
                if (drawing[j * 9 + i] == Paint.Prim) {
                    gwafics.setCharacter(new TerminalPosition(x + i, y + j), ' ');
                }
                if (drawing[j * 9 + i] == Paint.Scnd) {
                    gwafics.setCharacter(new TerminalPosition(x + i, y + j), '#');
                }
            }
        }
    }

    public void drawCheck(Screen screen, King king, Board board) {
        if (king.isInCheck(board)) {
            TextGraphics gwafics = screen.newTextGraphics();
            int charactersToFill = BLOCK_SIZE;
            int i = king.getPosition().getX();
            int j = king.getPosition().getY();
            gwafics.setBackgroundColor(new TextColor.RGB(128, 0, 1));
            gwafics.fillRectangle(new TerminalPosition(i * charactersToFill, j * charactersToFill),
                    new TerminalSize(BLOCK_SIZE, BLOCK_SIZE), ' ');
            drawPiece(screen, king);
        }
    }
}
