# language: en
Feature: Flashcards
    As a user, I want to have flashcards that speak what I want to say, so that I can communicate with other people more easily.

    Background:
        Given the User is in the App

    Rule: All Flashcards are easy to read and to understand
        As they might be the primary source of communication, their ease of use is mandatory

        Example: Add a Flashcard (Menu appears)
            Given the User is in the Flashcard section
            When the User clicks to add a new Flashcard
            Then a Menu appears
            And the User is able to type text

        Example: Add a Flashcard (write text)
            Given the User is in the Flashcard Menu
            And the User already typed something
            When the User clicks "Save"
            Then the Flashcard appears in the interface of Flashcards
            But the Menu is still active for more Flashcards

        Scenario Outline: Check an existing Flashcard
            Given there is at least one Flashcard
            When the User clicks it
            Then <title> appears on the screen
            And <subtitle> appears on the screen
            And <content> appears on the screen

            Scenarios:
                | title   | subtitle        | content                                              |
                | State   | Happy           | I'm very happy right now :D !                        |
                | State   | Sad             | I'm sorry, I don't feel good right now               |
                | State   | Disturbed       | PLEASE, MAKE IT STOP!                                |
                | Need    | To Drink        | I need to drink, preferably water                    |
                | Need    | To Sleep        | I feel sleepy now. Need to rest a little             |
                | Desire  | Pet the dog     | That is a cute dog. I want to pet it                 |
                | Desire  | Read a book     | I do enjoy literature in these fine times            |
                | Thought | Like            | I'm keen on that!                                    |
                | Thought | Dislike         | That does not please me. At all.                     |
                | State   | Bittersweetness | I like things that are happy and things that are sad |

        Example: Change a Flashcard
            Given there is at least one Flashcard
            When the User clicks to change a Flashcard
            Then the Flashcard Menu appears
            And the User is able to change the text

        Example: Delete a Flashcard
            Given there is at least one Flashcard
            When the User clicks to delete a Flashcard
            Then a success message appears
            And the Flashcard is deleted
