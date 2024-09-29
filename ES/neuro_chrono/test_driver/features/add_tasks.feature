# language: en
Feature: Add Tasks to Blocks
    As a user, I want to add tasks to my blocks, so that I don't need to waste time thinking about what to do at the beginning of an activity.

    Background:
        Given there is at least one Block

    Rule: All blocks must have the possibility to, at least, assign one task

        Example: Add a task (creation of block)
            Given the User is in the Block Menu
            When the User writes a Task
            And taps "Create"
           Then the User goes back to the Planner page
           And the Block has that Task assigned

        Example: Add a task (edition of block)
            Given the User is in the Block Menu
            When the User writes a Task (first or not)
            And taps "Save Changes"
            Then the User goes back to the Planner page
            And the Block has that Task assigned
        
        Example: Remove a task
            Given the User is in the Block Menu
            When the User clicks on the "Edit Task" button for a specific Task
            And the User clicks on the "Remove Task" button
            Then the Task is removed from the Block

        Example: Edit a task
            Given the User is in the Block Menu
            When the User clicks on the "Edit Task" button for a specific Task
            And the User writes the new Task in the "Edit Task" field
            And the User clicks on the "Save Task" button
            Then the Task is updated in the Block
