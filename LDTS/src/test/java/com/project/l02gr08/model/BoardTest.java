
package com.project.l02gr08.model;

import com.project.l02gr08.model.pieces.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class BoardTest {
    Board board;

    @BeforeEach
    void setUp() {
        board = new Board();
    }

    private List<Piece> getExpectedInitial() {
        List<Piece> expectedInitial = new ArrayList<>();
        expectedInitial.add(new Rook(Piece.Team.BLACK, new Position(0, 0)));
        expectedInitial.add(new Knight(Piece.Team.BLACK, new Position(1, 0)));
        expectedInitial.add(new Bishop(Piece.Team.BLACK, new Position(2, 0)));
        expectedInitial.add(new Queen(Piece.Team.BLACK, new Position(3, 0)));
        expectedInitial.add(new King(Piece.Team.BLACK, new Position(4, 0)));
        expectedInitial.add(new Bishop(Piece.Team.BLACK, new Position(5, 0)));
        expectedInitial.add(new Knight(Piece.Team.BLACK, new Position(6, 0)));
        expectedInitial.add(new Rook(Piece.Team.BLACK, new Position(7, 0)));
        for (int i = 0; i < 8; ++i) {
            expectedInitial.add(new Pawn(Piece.Team.BLACK, new Position(i, 1)));
        }
        expectedInitial.add(new Rook(Piece.Team.WHITE, new Position(0, 7)));
        expectedInitial.add(new Knight(Piece.Team.WHITE, new Position(1, 7)));
        expectedInitial.add(new Bishop(Piece.Team.WHITE, new Position(2, 7)));
        expectedInitial.add(new Queen(Piece.Team.WHITE, new Position(3, 7)));
        expectedInitial.add(new King(Piece.Team.WHITE, new Position(4, 7)));
        expectedInitial.add(new Bishop(Piece.Team.WHITE, new Position(5, 7)));
        expectedInitial.add(new Knight(Piece.Team.WHITE, new Position(6, 7)));
        expectedInitial.add(new Rook(Piece.Team.WHITE, new Position(7, 7)));
        for (int i = 0; i < 8; ++i) {
            expectedInitial.add(new Pawn(Piece.Team.WHITE, new Position(i, 6)));
        }
        return expectedInitial;
    }

    private List<Piece> getExpectedAfterMove() {
        List<Piece> expectedAfterMove = new ArrayList<>();
        expectedAfterMove.add(new Rook(Piece.Team.BLACK, new Position(0, 0)));
        expectedAfterMove.add(new Knight(Piece.Team.BLACK, new Position(1, 0)));
        expectedAfterMove.add(new Bishop(Piece.Team.BLACK, new Position(2, 0)));
        expectedAfterMove.add(new Queen(Piece.Team.BLACK, new Position(3, 0)));
        expectedAfterMove.add(new King(Piece.Team.BLACK, new Position(4, 0)));
        expectedAfterMove.add(new Knight(Piece.Team.BLACK, new Position(6, 0)));
        expectedAfterMove.add(new Rook(Piece.Team.BLACK, new Position(7, 0)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(0, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(1, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(2, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(3, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(5, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(6, 1)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(7, 1)));
        expectedAfterMove.add(new Rook(Piece.Team.WHITE, new Position(0, 7)));
        expectedAfterMove.add(new Knight(Piece.Team.WHITE, new Position(1, 7)));
        expectedAfterMove.add(new Bishop(Piece.Team.WHITE, new Position(2, 7)));
        expectedAfterMove.add(new Queen(Piece.Team.WHITE, new Position(3, 7)));
        expectedAfterMove.add(new Bishop(Piece.Team.WHITE, new Position(5, 7)));
        expectedAfterMove.add(new Knight(Piece.Team.WHITE, new Position(6, 7)));
        expectedAfterMove.add(new Rook(Piece.Team.WHITE, new Position(7, 7)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(0, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(1, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(2, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(4, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(6, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(7, 6)));

        // Modified pieces from the original board
        expectedAfterMove.add(new Bishop(Piece.Team.BLACK, new Position(4, 7)));
        expectedAfterMove.add(new Pawn(Piece.Team.BLACK, new Position(4, 3)));
        expectedAfterMove.add(new King(Piece.Team.WHITE, new Position(5, 6)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(3, 4)));
        expectedAfterMove.add(new Pawn(Piece.Team.WHITE, new Position(5, 4)));

        return expectedAfterMove;
    }

    private List<Position> getExpectedMoves() {
        List<Position> expectedMoves = new ArrayList<>();
        expectedMoves.add(new Position(4, 5));
        expectedMoves.add(new Position(5, 5));
        expectedMoves.add(new Position(4, 7));
        return expectedMoves;
    }

    private List<Position> getExpectedRemoveToCheckMoves() {
        List<Position> expectedMoves = new ArrayList<>();
        expectedMoves.add(new Position(1, 2));
        expectedMoves.add(new Position(2, 3));
        expectedMoves.add(new Position(1, 4));
        expectedMoves.add(new Position(2, 2));
        expectedMoves.add(new Position(2, 4));
        return expectedMoves;
    }

    private List<Position> getExpectedRemoveStillInCheckMoves() {
        List<Position> expectedMoves = new ArrayList<>();
        expectedMoves.add(new Position(2, 3));
        expectedMoves.add(new Position(2, 2));
        expectedMoves.add(new Position(2, 4));
        return expectedMoves;
    }

    private List<Piece> getCheckmateBoard() {
        List<Piece> pieces = new ArrayList<>();
        pieces.add(new Rook(Piece.Team.BLACK, new Position(0, 0)));
        pieces.add(new Knight(Piece.Team.BLACK, new Position(1, 0)));
        pieces.add(new Bishop(Piece.Team.BLACK, new Position(2, 0)));
        pieces.add(new King(Piece.Team.BLACK, new Position(4, 0)));
        pieces.add(new Bishop(Piece.Team.BLACK, new Position(5, 0)));
        pieces.add(new Knight(Piece.Team.BLACK, new Position(6, 0)));
        pieces.add(new Rook(Piece.Team.BLACK, new Position(7, 0)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(0, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(1, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(2, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(3, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(5, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(6, 1)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(7, 1)));
        pieces.add(new Rook(Piece.Team.WHITE, new Position(0, 7)));
        pieces.add(new Knight(Piece.Team.WHITE, new Position(1, 7)));
        pieces.add(new Bishop(Piece.Team.WHITE, new Position(2, 7)));
        pieces.add(new Queen(Piece.Team.WHITE, new Position(3, 7)));
        pieces.add(new King(Piece.Team.WHITE, new Position(4, 7)));
        pieces.add(new Bishop(Piece.Team.WHITE, new Position(5, 7)));
        pieces.add(new Knight(Piece.Team.WHITE, new Position(6, 7)));
        pieces.add(new Rook(Piece.Team.WHITE, new Position(7, 7)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(0, 6)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(1, 6)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(2, 6)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(3, 6)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(4, 6)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(7, 6)));

        // Modified pieces from the original board
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(5, 5)));
        pieces.add(new Pawn(Piece.Team.WHITE, new Position(6, 4)));
        pieces.add(new Pawn(Piece.Team.BLACK, new Position(4, 3)));
        pieces.add(new Queen(Piece.Team.BLACK, new Position(7, 4)));

        return pieces;
    }

    private List<Piece> getRemoveToCheckMovesBoard() {
        List<Piece> pieces = new ArrayList<>();
        pieces.add(new Rook(Piece.Team.WHITE, new Position(0, 0)));
        pieces.add(new King(Piece.Team.WHITE, new Position(1, 0)));
        pieces.add(new King(Piece.Team.BLACK, new Position(1, 3)));
        return pieces;
    }

    private List<Piece> getRemoveStillInCheckMovesBoard() {
        List<Piece> pieces = new ArrayList<>();
        pieces.add(new Rook(Piece.Team.WHITE, new Position(0, 0)));
        pieces.add(new Rook(Piece.Team.WHITE, new Position(1, 0)));
        pieces.add(new King(Piece.Team.WHITE, new Position(2, 0)));
        pieces.add(new King(Piece.Team.BLACK, new Position(1, 3)));
        return pieces;
    }

    private boolean theSamePiece(List<Piece> list1, List<Piece> list2) {
        Comparator<Piece> comparatorPieces = (p1, p2) -> {
            if (p1.getPosition().getY() == p2.getPosition().getY()) {
                return p1.getPosition().getX() - p2.getPosition().getX();
            }
            return p1.getPosition().getY() - p2.getPosition().getY();
        };

        list1.sort(comparatorPieces);
        list2.sort(comparatorPieces);

        if (list1.size() != list2.size()) {
            return false;
        }

        for (int i = 0; i < list1.size(); ++i) {
            if (list1.get(i).getClass() != list2.get(i).getClass()) {
                return false;
            }
            if (list1.get(i).getTeam() != list2.get(i).getTeam()) {
                return false;
            }
            if (list1.get(i).getPosition().getX() != list2.get(i).getPosition().getX()) {
                return false;
            }
            if (list1.get(i).getPosition().getY() != list2.get(i).getPosition().getY()) {
                return false;
            }
        }
        return true;
    }

    private boolean theSamePosition(List<Position> list1, List<Position> list2) {
        Comparator<Position> comparatorPositions = (p1, p2) -> {
            if (p1.getY() == p2.getY()) {
                return p1.getX() - p2.getX();
            }
            return p1.getY() - p2.getY();
        };

        list1.sort(comparatorPositions);
        list2.sort(comparatorPositions);

        if (list1.size() != list2.size()) {
            return false;
        }

        for (int i = 0; i < list1.size(); ++i) {
            if (list1.get(i).getX() != list2.get(i).getX()) {
                return false;
            }
            if (list1.get(i).getY() != list2.get(i).getY()) {
                return false;
            }
        }
        return true;
    }

    // ======================================================================================

    @Test
    void testConstructor() {
        Board board = new Board();
        List<Piece> inBoard = board.getPieces();

        Assertions.assertTrue(theSamePiece(inBoard, getExpectedInitial()));
    }

    @Test
    void testMovePiece() {
        Board board = new Board();
        board.movePiece(board.pieceAt(new Position(5, 6)).get(), new Position(5, 4));
        board.movePiece(board.pieceAt(new Position(4, 1)).get(), new Position(4, 3));
        board.movePiece(board.pieceAt(new Position(3, 6)).get(), new Position(3, 4));
        board.movePiece(board.pieceAt(new Position(5, 0)).get(), new Position(1, 4));
        board.movePiece(board.pieceAt(new Position(4, 7)).get(), new Position(5, 6));
        board.movePiece(board.pieceAt(new Position(1, 4)).get(), new Position(4, 7));
        List<Piece> inBoard = board.getPieces();

        Assertions.assertTrue(theSamePiece(inBoard, getExpectedAfterMove()));
    }

    @Test
    void testGetRecommendedMoves() {
        Board board = new Board(getExpectedAfterMove());
        Assertions.assertFalse(board.isCheck(Piece.Team.BLACK));
        Assertions.assertTrue(board.isCheck(Piece.Team.WHITE));

        Piece knight = board.pieceAt(new Position(6, 7)).get();
        Assertions.assertEquals(knight.generateRecommendedMoves(board).size(), 0);

        Piece bishop = board.pieceAt(new Position(2, 7)).get();
        Assertions.assertEquals(bishop.generateRecommendedMoves(board).size(), 0);

        Piece queen = board.pieceAt(new Position(3, 7)).get();
        Assertions.assertEquals(queen.generateRecommendedMoves(board).size(), 1);

        Piece pawn = board.pieceAt(new Position(0, 6)).get();
        Assertions.assertEquals(pawn.generateRecommendedMoves(board).size(), 0);

        King king = board.findKing(Piece.Team.WHITE).get();
        Assertions.assertTrue(theSamePosition(king.generateRecommendedMoves(board), getExpectedMoves()));
    }

    @Test
    void testIsCheckMate() {
        Assertions.assertFalse(board.isCheckMate(Piece.Team.WHITE));
        Assertions.assertFalse(board.isCheckMate(Piece.Team.BLACK));

        Board board = new Board(getCheckmateBoard());
        Assertions.assertTrue(board.isCheckMate(Piece.Team.WHITE));
        Assertions.assertFalse(board.isCheckMate(Piece.Team.BLACK));

        board = new Board(getExpectedAfterMove());
        Assertions.assertFalse(board.isCheckMate(Piece.Team.WHITE));
        Assertions.assertFalse(board.isCheckMate(Piece.Team.BLACK));
    }

    @Test
    void testRemoveToCheckMoves() {
        Board board = new Board(getRemoveToCheckMovesBoard());
        Piece king = board.pieceAt(new Position(1, 3)).get();

        Assertions.assertTrue(
                theSamePosition(getExpectedRemoveToCheckMoves(), king.generateRecommendedMoves(board))
        );
    }

    @Test
    void testRemoveStillInCheckMoves() {
        Board board = new Board(getRemoveStillInCheckMovesBoard());
        Piece king = board.pieceAt(new Position(1, 3)).get();

        Assertions.assertTrue(
                theSamePosition(getExpectedRemoveStillInCheckMoves(), king.generateRecommendedMoves(board))
        );
    }
}

