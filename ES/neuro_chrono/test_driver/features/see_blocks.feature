# language: en
Feature: See the Daily Schedule
    Usually, the User will open the app on this section

    Rule: The Schedule page must always be somehow visible
        Even if it is empty, there should a button to create a new block

        Example: There is at least one Block (app open)

            Given the User is in the App
            And the User is logged in with an account with blocks
            But not in the "Schedule" page
            When the User taps the "Schedule" page
            Then the App goes to the "Schedule" page
            And there is at least one block

        Example: There aren't any Blocks

            Given the User is in the App
            And the User is logged in with an account with zero blocks
            But not in the "Schedule" page
            When the User taps the "Schedule" page
            Then the App goes to the "Schedule" page
            And there are zero blocks
    
