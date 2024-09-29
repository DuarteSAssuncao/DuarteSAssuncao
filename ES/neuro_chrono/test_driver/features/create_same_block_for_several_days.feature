Feature: Create the same Block for several days
  As a user, I want to be able to create the same block for several days at the same time, so that I don't have to repeat myself when creating the blocks

  Background:
    Given the User is signed in

  Rule: All Blocks of all types can be cross-day
    Meaning it can be present in various days

  Example: Create a Block for various days (enough space)
    Given there is space in day A
    And there is space in day B
    When the User taps to create a Block
    And the User selects day A and day B
    Then the Block appears in day A
    And the Block appears in day B

  Example: Create a Block for various days (not enough space)
    Given there is space in day A
    But there isn't enough space in day B
    When the User taps to create a Block
    And the User selects day A and day B
    Then a warning appears
    And the Blocks are not created
