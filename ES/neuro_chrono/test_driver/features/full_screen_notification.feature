# language: en
Feature: Full Screen reminder of a Block
    When the User is in the App and a block is about to start, a full screen notification appears

    Background:
        Given there is one block
        And one block is about to start

    Rule: The User must be notified

        Example: The time of the start of the block is the same as the current time
            Given the User is in the App
            When the starting time of the block arrives
            Then the User is in the "Notification" page
