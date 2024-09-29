# language: en
Feature: Have an Account
  As a user, I want to have an account associated to my schedule and the ability to log in and log out of that account, so that I can access it on more devices at the same time

  Background:
    Given the User has the app installed

    Rule: The User must have control over their account
      They must be able to create, delete and possibly modify it

    Example: Creating an account (non-existent, matching passwords)
      Given there isn't an account with the User credentials
      When the User fills the form with their credentials
      And the Password and Repeat Password match
      Then the Account is successfully created
      And the User is redirected to the Planner Page

    Example: Creating an account (non-existent, different passwords)
      Given there isn't an account with the User credentials
      When the User fills the form with their credentials
      But the Password and Repeat Password don't match
      Then the Account isn't created
      And an error appears

    Example: Creating an account (existent, matching passwords)
      Given there is an account with the User credentials
      When the User fills the form with their credentials
      And the Password and Repeat Password match
      Then the Account isn't created
      And an error about account already existent appears

    Example: Creating an account (existent, different passwords)
      Given there is an account with the User credentials
      When the User fills the form with their credentials
      But the Password and Repeat Password don't match
      Then the Account isn't created
      And an error about account already existent appears

    Example: Signing in (matching credentials)
      Given there is an account with the User credentials
      When the User fills the form with their credentials
      And the credentials are correct
      Then the User signs in
      And the User is redirected to the Planner Page

    Example: Signing in (different credentials)
      Given there is an account with the User credentials
      When the User fills the form with their credentials
      But the credentials (user and/or email) aren't correct
      Then the User doesn't sign in
      And an error about wrong credentials appears
      And the password field is cleared

    Example: Signing in (non-existent account)
      Given there isn't an account with the User credentials
      When the User fills the form with their credentials
      Then the User doesn't sign in
      And an error about no account appears
      And the password field is cleared

    Example: Sign out
      Given there is an account with the User credentials
      And the User is signed in
      When the User taps "Sign Out"
      Then the User signs out
      And the Login Page appears
