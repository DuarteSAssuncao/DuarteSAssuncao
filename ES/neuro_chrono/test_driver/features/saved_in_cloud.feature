# language: en
Feature: Schedule save in the cloud
  So that it stays synchronized between devices

  Background:
    Given the User has an existing account

    Rule: All Blocks should be present and be present in all devices

    Example: Check Planner (same device, no Blocks)
      Given the User is signed in
      And the Planner has zero Blocks
      When the User is in the Planner Page
      Then no Blocks are visible
      But the User can create Blocks

    Example: Check Planner (same device, at least one Block)
      Given the User is signed in
      And the Planner has at least one Block
      When the User is in the Planner Page
      And the User is in a day with at least one Block
      Then at least one Block appears

    Example: Check Planner (different devices, no Blocks)
      Given the User is signed in in Device A and in Device B
      And the Planner has zero Blocks in Device B
      When the User is in the Planner Page in Device A
      Then no Blocks are visible
      But the User can create Blocks

    Example: Check Planner (different devices, at least one Block)
      Given the User is signed in in Device A and in Device B
      And the Planner has at least one Block in Device B
      When the User is in the Planner Page in Device A
      And the User is in a day with at least one Block
      Then at least one Block appears
      And the Blocks are equal

    Example: Create a Block
      Given the User is signed in in Device A and in Device B
      And a Block can be created
      When the User creates a Block in Device B
      And updates the App in Device A
      Then the new Block appears
      And it is the same Block

    Example: Edit Block
      Given the User is signed in in Device A and in Device B
      And there is at least one Block
      When the User edits a Block in Device B
      And updates the App in Device A
      Then the same Block in Device A is updated
      And the changes are the same

    Example: Delete Block
      Given the User is signed in in Device A and in Device B
      And there is at least one Block
      When the User deletes a Block in Device B
      And updates the App in Device A
      Then the same Block in Device A is deleted
