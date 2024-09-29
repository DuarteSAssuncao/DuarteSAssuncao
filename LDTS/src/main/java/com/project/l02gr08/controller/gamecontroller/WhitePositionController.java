package com.project.l02gr08.controller.gamecontroller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.controller.EndController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.state.gamestate.ChoiceState;
import com.project.l02gr08.state.EndState;
import com.project.l02gr08.state.gamestate.PositionState;
import com.project.l02gr08.viewer.EndViewer;
import com.project.l02gr08.viewer.gameviewer.ChoiceViewer;

import java.util.List;

public class WhitePositionController implements PositionController {
    @Override
    public void step(KeyStroke key, Game game) {
        PositionState state = (PositionState) game.getState();
        Piece selected = state.getSelectedPiece();
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
                selected.move(board, cursorPosition);
                if (board.isCheckMate(Piece.Team.BLACK)) {
                    System.out.println("White wins!");
                    EndState nextState = new EndState(new EndController(), new EndViewer(), "WHITE");
                    game.setState(nextState);
                } else {
                    ChoiceState nextState = new ChoiceState(new BlackChoiceController(), new ChoiceViewer(), board);
                    game.setState(nextState);
                }
                return;

            case Escape:
                ChoiceState prevState = new ChoiceState(new WhiteChoiceController(), new ChoiceViewer(), board);
                game.setState(prevState);
                return;

            default:
        }
    }

    @Override
    public Position preferredInitialCursor(Board b) {
        return new Position(b.getBoardLength() - 1, b.getBoardLength() - 1);
    }

    @Override
    public boolean isValid(KeyType key, PositionState state) {
        Board board = state.getBoard();
        Position pos = state.getCursor();
        Piece selected = state.getSelectedPiece();
        switch (key) {
            case ArrowUp:
                return pos.getUp().getY() >= 0;

            case ArrowDown:
                return pos.getDown().getY() <= 7;

            case ArrowLeft:
                return pos.getLeft().getX() >= 0;

            case ArrowRight:
                return pos.getRight().getX() <= 7;

            case Enter:
                List<Position> valids = selected.generateRecommendedMoves(board);
                for (Position poses : valids) {
                    if (poses.equals(pos))
                        return true;
                }
                return false;

            case Escape:
                return true;

            default:
                return false;
        }
    }
}
