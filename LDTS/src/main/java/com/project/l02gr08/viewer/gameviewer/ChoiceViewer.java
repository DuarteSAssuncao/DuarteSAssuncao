package com.project.l02gr08.viewer.gameviewer;

import com.googlecode.lanterna.screen.Screen;
import com.googlecode.lanterna.screen.Screen.RefreshType;
import com.project.l02gr08.Game;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.pieces.King;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.state.gamestate.ChoiceState;

import java.io.IOException;

public class ChoiceViewer extends GameViewer {
    @Override
    public void draw(Game game) throws IOException {
        Screen screen = game.getGUI().getScreen();
        ChoiceState gs = (ChoiceState) game.getState();
        Board board = gs.getBoard();
        drawBoard(screen, gs);
        for (Piece piece : board.getPieces()) {
            if (piece instanceof King) {
                drawCheck(screen, (King) piece, board);
            }
            drawPiece(screen, piece);
        }
        drawCursor(screen, gs);
        screen.refresh(RefreshType.DELTA);
    }
}
