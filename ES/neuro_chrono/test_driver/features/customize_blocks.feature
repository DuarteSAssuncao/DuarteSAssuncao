# language: en
Feature: Customize the Blocks
    If the User decides to change an already existing block, they should be allowed to do so

    Background:
        Given the User created at least one Block
        And the User is in the "Schedule" page

    Rule: Any block, including Basic Necessity ones, should be editable

        Example: Reallocating a Block (valid changes)
            Given there is enough free space in the Schedule
            When the User taps the block
            Then the "EditBlock" page appears
            When the User changes it to a valid interval
            Then the Block is removed from the old interval
            And the Block is placed on the new interval
            And the User is redirected to the "Schedule" page

        Scenario Outline: Reallocating a Block (overlapping)
            Given there is a Block starting at <a> and ending at <b>
            When the User taps the block
            Then the "EditBlock" page appears
            When the User changes the starting time to <shour>
            Then a warning appears
            And the Block does not change

            Scenarios:
                |shour|  a  |  b  |
                |17:00|17:00|18:00|
                |16:00|15:45|16:15|
                |13:00|12:00|14:00|
                |09:00|08:00|11:00|

        Example: Changing type
            When the User taps the block
            Then the "EditBlock" page appears
            When the User changes the type
            Then the type of the Block is updated
            And the User is redirected to the Schedule page

        Example: Cancel
            When the User taps the block
            Then the "EditBlock" page appears
            When the User taps the "X" button
            Then the User is redirected to the "Schedule" page

        Example: Delete a Block
            When the User taps the block
            Then the "EditBlock" page appears
            When the User taps the "Delete" button
            Then the Block is removed from the Schedule
            And the User is redirected to the Schedule page
