package com.project.l02gr08.viewer.gameviewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.Screen.RefreshType;
import com.project.l02gr08.Game;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.King;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.state.gamestate.PositionState;

import java.io.IOException;

public class PositionViewer extends GameViewer {
    @Override
    public void draw(Game game) throws IOException {
        PositionState gs = (PositionState) game.getState();
        Board board = gs.getBoard();
        Screen screen = game.getGUI().getScreen();
        drawBoard(screen, gs);
        TextGraphics gwafics = screen.newTextGraphics();
        Piece target = gs.getSelectedPiece();
        gwafics.setBackgroundColor(new TextColor.RGB(130, 130, 130));
        for (Position pos : target.generateRecommendedMoves(board)) {
            int x = pos.getX() * BLOCK_SIZE;
            int y = pos.getY() * BLOCK_SIZE;
            gwafics.fillRectangle(new TerminalPosition(x, y),
                    new TerminalSize(BLOCK_SIZE, BLOCK_SIZE), ' ');
        }
        for (Piece p : board.getPieces()) {
            if (p instanceof King) {
                drawCheck(screen, (King) p, board);
            }
            drawPiece(screen, p);
        }
        drawCursor(screen, gs);
        screen.refresh(RefreshType.DELTA);
    }
}
