
package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class KingTest implements PieceTest {
    Board emptyBoard;
    List<Position> emptyExpected;
    Board filledSameBoard;
    List<Position> filledSameExpected;
    Board filledDifferentBoard;
    List<Position> filledDifferentExpected;
    Board initialBoard;
    List<Position> initialExpected;
    Board castlingBoard;
    List<Position> shortCastlingExpected;
    List<Position> longCastlingExpected;

    @BeforeEach
    @Override
    public void setUp() {
        List<Piece> pieces = List.of(new King(Piece.Team.WHITE, new Position(3, 3)));
        emptyBoard = new Board(pieces);
        emptyExpected = List.of(
                new Position(2, 2),
                new Position(2, 3),
                new Position(2, 4),
                new Position(3, 2),
                new Position(3, 4),
                new Position(4, 2),
                new Position(4, 3),
                new Position(4, 4)
        );

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                pieces.add(new King(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledSameBoard = new Board(pieces);
        filledSameExpected = new ArrayList<>();

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                if (i == 3 && j == 3) {
                    pieces.add(new King(Piece.Team.BLACK, new Position(i, j)));
                }
                pieces.add(new King(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledDifferentBoard = new Board(pieces);
        filledDifferentExpected = List.of(
                new Position(2, 2),
                new Position(2, 3),
                new Position(2, 4),
                new Position(3, 2),
                new Position(3, 4),
                new Position(4, 2),
                new Position(4, 3),
                new Position(4, 4)
        );

        initialBoard = new Board();
        initialExpected = new ArrayList<>();

        pieces = new ArrayList<>();
        pieces.add(new King(Piece.Team.BLACK, new Position(4, 0)));
        pieces.add(new Rook(Piece.Team.BLACK, new Position(0, 0)));
        pieces.add(new King(Piece.Team.WHITE, new Position(4, 7)));
        pieces.add(new Rook(Piece.Team.WHITE, new Position(7, 7)));
        castlingBoard = new Board(pieces);
        shortCastlingExpected = List.of(
                new Position(3, 7),
                new Position(3, 6),
                new Position(4, 6),
                new Position(5, 6),
                new Position(5, 7),
                new Position(6, 7)
        );
        longCastlingExpected = List.of(
                new Position(3, 0),
                new Position(3, 1),
                new Position(4, 1),
                new Position(5, 1),
                new Position(5, 0),
                new Position(2, 0)
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
        Piece piece = initialBoard.pieceAt(new Position(4, 0)).get();
        List<Position> legalMoves = piece.generateMoves(initialBoard);
        Assertions.assertTrue(isSame(legalMoves, initialExpected));
    }

    @Override
    @Test
    public void hasDrawing() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertNotNull(piece.getDrawing());
    }

    @Test
    public void testIsCheck() {
        King king = (King) emptyBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertFalse(king.isInCheck(emptyBoard));
        king = (King) filledSameBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertFalse(king.isInCheck(filledSameBoard));
        king = (King) filledDifferentBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertTrue(king.isInCheck(filledDifferentBoard));
        king = (King) initialBoard.pieceAt(new Position(4, 0)).get();
        Assertions.assertFalse(king.isInCheck(initialBoard));
    }

    @Test
    public void testCastling() {
        King king = (King) castlingBoard.pieceAt(new Position(4, 7)).get();
        List<Position> legalMoves = king.generateMoves(castlingBoard);
        Assertions.assertTrue(isSame(legalMoves, shortCastlingExpected));

        king.move(castlingBoard, new Position(6, 7));
        Assertions.assertEquals(king, castlingBoard.pieceAt(new Position(6, 7)).get());
        Piece rook = castlingBoard.pieceAt(new Position(5, 7)).get();
        Assertions.assertEquals(Rook.class, rook.getClass());
        Assertions.assertEquals(Piece.Team.WHITE, rook.getTeam());
        Assertions.assertEquals(new Position(5, 7), rook.getPosition());


        king = (King) castlingBoard.pieceAt(new Position(4, 0)).get();
        legalMoves = king.generateMoves(castlingBoard);
        Assertions.assertTrue(isSame(legalMoves, longCastlingExpected));

        king.move(castlingBoard, new Position(2, 0));
        Assertions.assertEquals(king, castlingBoard.pieceAt(new Position(2, 0)).get());
        rook = castlingBoard.pieceAt(new Position(3, 0)).get();
        Assertions.assertEquals(Rook.class, rook.getClass());
        Assertions.assertEquals(Piece.Team.BLACK, rook.getTeam());
        Assertions.assertEquals(new Position(3, 0), rook.getPosition());
    }
}

