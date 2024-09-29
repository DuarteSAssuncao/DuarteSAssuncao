# language: en
Feature: Deactivate full-screen notifications
  The push notifications will still be active

  Background:
    Given the User is signed in

  Rule: All full-screen notifications are deactivated
    Both the on-time and five-minutes-early

  Example: Full-screen notifications off (on-time)
    Given there is at least one Block
    And Full-screen Notifications are deactivated
    When the Block starts
    Then the on-time notification does not appear
    But the push notification appears

  Example: Full-screen notifications off (five-minutes-early)
    Given there is at least one Block
    And Full-screen Notifications are deactivated
    When the Block ends in five minutes
    Then the five-minutes-early notification does not appear
    But the push notification appears

  Example: Full-screen notifications on (on-time)
    Given there is at least one Block
    And Full-screen Notifications are ctivated
    When the Block starts
    Then the on-time notification appears
    And the push notification appears

  Example: Full-screen notifications on (five-minutes-early)
    Given there is at least one Block
    And Full-screen Notifications are activated
    When the Block ends in five minutes
    Then the five-minutes-early notification appears
    And the push notification appears
