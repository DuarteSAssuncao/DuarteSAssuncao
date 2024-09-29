# language: en
Feature: All Blocks have a previously user defined custom type
  This gives freedom of choice to the User

  Background:
    Given the User is signed in

  Rule: All types are custom and have a unique color and name
    So as to not confuse the user

  Example: Create a Block (no types available)
    Given there are no types available
    When the User taps to create a Block
    And the User taps the Type Dropdown
    Then the Type Dropdown is empty
    And the User can't choose any type

  Example: Create a Block (at least one type available)
    Given there is a type available
    When the User taps to create a Block
    And the User taps the Type Dropdown
    Then at least one type appears
    And the User can choose one of them

  Example: Edit a Block
    Given there are at least two types available
    When the User taps a Block
    And the User taps the Type Dropdown
    Then at least two types appear
    And the User can choose another type

  Example: Block in Planner Page
    Given there is space available in the Planner Page
    When the User creates a Block
    Then the name of the Block is its type
    And the color of the Block is the color of its type
