package com.project.l02gr08.controller.gamecontroller;

import java.util.Optional;
import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.model.pieces.Piece.Team;
import com.project.l02gr08.state.gamestate.ChoiceState;
import com.project.l02gr08.state.gamestate.PositionState;
import com.project.l02gr08.viewer.gameviewer.PositionViewer;

public class WhiteChoiceController implements ChoiceController {
    @Override
    public void step(KeyStroke key, Game game) {
        ChoiceState state = (ChoiceState) game.getState();
        Board board = state.getBoard();
        Position cursorPosition = state.getCursor();
        KeyType key_info = key.getKeyType();

        if (!isValid(key_info, state)) return;
        switch (key_info) {
            case ArrowUp:
                state.setCursor(cursorPosition.getUp());
                return;

            case ArrowDown:
                state.setCursor(cursorPosition.getDown());
                return;

            case ArrowLeft:
                state.setCursor(cursorPosition.getLeft());
                return;

            case ArrowRight:
                state.setCursor(cursorPosition.getRight());
                return;

            case Enter:
                PositionState nextState = new PositionState(new WhitePositionController(), new PositionViewer(), board, board.pieceAt(cursorPosition).get());
                game.setState(nextState);
                return;

            default:
        }
    }

    @Override
    public Position preferredInitialCursor(Board b) {
        return new Position(0, b.getBoardLength() - 1);
    }

    @Override
    public boolean isValid(KeyType key, ChoiceState state) {
        Board board = state.getBoard();
        Position pos = state.getCursor();
        switch (key) {
            case ArrowUp:
                return !(pos.getUp().getY() < 0);

            case ArrowDown:
                return !(pos.getDown().getY() > 7);

            case ArrowLeft:
                return !(pos.getLeft().getX() < 0);

            case ArrowRight:
                return !(pos.getRight().getX() > 7);

            case Enter:
                Optional<Piece> p = board.pieceAt(pos);
                if (p.isPresent()) {
                    if (p.get().getTeam() == Team.WHITE && !p.get().generateRecommendedMoves(board).isEmpty())
                        return true;
                }
                return false;
            default:
                return false;
        }
    }
}
