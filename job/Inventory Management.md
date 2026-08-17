# Inventory And UI System

Built an inventory system that allows the player to add and remove items through a UI.

## Inventory System

The inventory System can be found through Inventory, pickup, and base item folders. The inventory is built with slots that can be customized for the default it only allows a max item slots of 32. Allow items that can go into the inventory must be a pick up item object. You can find the details for a pickup item in the pick up item folder.

## UI system

All the UI systems must go through the manager HUD widget which handles the transition between UI widgets. You can find the details for UI in the HUD folder.

## Interaction

All items implement a Interact function, so that each item can have its own custom interaction with the player. The pawn will handle how to manage each item, but for now all that it does it add it to the players inventory.

<img src="../_resources/interaction%20and%20inventory%20clip.gif" alt="interaction and inventory clip.gif" width="683" height="427">

# Health and respawn system

Press o to deplete the player's health bar and when it reaches 0 the player will die and respawn as the same pawn. You can customize the players health and how much damage you can deal to yourself.

<img src="../_resources/health%20and%20respawn%20clip.gif" alt="health and respawn clip.gif" width="635" height="397">