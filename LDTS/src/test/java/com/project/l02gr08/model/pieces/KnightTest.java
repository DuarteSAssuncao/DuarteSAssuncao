
package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class KnightTest implements PieceTest {
    Board emptyBoard;
    List<Position> emptyExpected;
    Board filledSameBoard;
    List<Position> filledSameExpected;
    Board filledDifferentBoard;
    List<Position> filledDifferentExpected;
    Board initialBoard;
    List<Position> initialExpected;

    @Override
    @BeforeEach
    public void setUp() {
        List<Piece> pieces = List.of(new Knight(Piece.Team.WHITE, new Position(3, 3)));
        emptyBoard = new Board(pieces);
        emptyExpected = List.of(
                new Position(1, 2), new Position(5, 2),
                new Position(2, 1), new Position(4, 1),
                new Position(2, 5), new Position(4, 5),
                new Position(1, 4), new Position(5, 4)
        );

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                pieces.add(new Knight(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledSameBoard = new Board(pieces);
        filledSameExpected = new ArrayList<>();

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                if (i == 3 && j == 3) {
                    pieces.add(new Knight(Piece.Team.BLACK, new Position(i, j)));
                }
                pieces.add(new Knight(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledDifferentBoard = new Board(pieces);
        filledDifferentExpected = List.of(
                new Position(1, 2), new Position(5, 2),
                new Position(2, 1), new Position(4, 1),
                new Position(2, 5), new Position(4, 5),
                new Position(1, 4), new Position(5, 4)
        );

        initialBoard = new Board();
        initialExpected = List.of(
                new Position(0, 5), new Position(2, 5)
        );
    }

    @Override
    @Test
    public void testInEmptyBoard() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(emptyBoard);
        Assertions.assertTrue(isSame(legalMoves, emptyExpected));
    }

    @Override
    @Test
    public void testInFilledSameBoard() {
        Piece piece = filledSameBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(filledSameBoard);
        Assertions.assertTrue(isSame(legalMoves, filledSameExpected));
    }

    @Override
    @Test
    public void testInFilledDifferentBoard() {
        Piece piece = filledDifferentBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(filledDifferentBoard);
        Assertions.assertTrue(isSame(legalMoves, filledDifferentExpected));
    }

    @Override
    @Test
    public void testInInitialBoard() {
        Piece piece = initialBoard.pieceAt(new Position(1, 7)).get();
        List<Position> legalMoves = piece.generateMoves(initialBoard);
        Assertions.assertTrue(isSame(legalMoves, initialExpected));
    }

    @Override
    @Test
    public void hasDrawing() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertNotNull(piece.getDrawing());
    }
}

