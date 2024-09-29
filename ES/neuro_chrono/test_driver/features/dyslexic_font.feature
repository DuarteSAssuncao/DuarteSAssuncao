# language: en
Feature: Open Dyslexic Font
  I don't think it's possible to dynamically change the font, so there are only two on acceptance test

  Background: None

  Rule: Everything must be in Open Dyslexic Font

  Example: Not signed in
    Given the User is not signed in
    When the User enters the App
    Then the font in the Login Page is OpenDyslexic
    And the font in the Register Page is OpenDyslexic

  Scenario Outline: Signed in
    Given the User is signed in
    When the User goes to the <page>
    Then the font is OpenDyslexic

    Scenarios:
      |       page      |
      | Planner Page    |
      | Settings        |
      | Types           |
      | Create a Block  |
      | Edit a Block    |
      | Notification    |
