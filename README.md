# DMG

This is a game that was inspired by a reddit post and those stupid clicker games that are everywhere. I kind of want to make my own stupid clicker game.

The premise of the post is that you have $1. You can choose to double your current money, or you can choose to keep the money. You have a 99.9% chance to double your money. If doubling the money fails, you don't get anything. How many times do you double your money before you choose to keep your money?

I created a small C program, a text-based game, that explored this concept. What I've found is: most of the time you are able to overflow an unsigned long, long before you fail to double your money. This question will have you crashing whatever economy you're in before you have to really consider stopping. Before creating this program, I had thought 14 Million was a good stopping point, when in reality a good stopping point would be any amount that doesn't crash the economy you're in.

With this in mind, there should be a bit more of an interesting setup for this. I'm not entirely sure what I would do differently, but this is what this new game is for.

## Game Loop

There will be a dual-currency to a multi-currency system. The player will earn "Percentage Points" by waiting. You can use "Percentage Points" to buy one-time use to increase percentages associated with a risk in game.

You are given $1 initially. You can risk to add a set amount e.g. $0.05, $0.10, $0.25, etc. Whatever makes sense to add. There will be a decent chance to reset back to $1 if you do not accept.

You are given a chance to double your money. There is a minimum amount and maximum amount for the percentage. The percentage is decreased slowly each time the button is pushed, but never going below the minimum. If you purchase percentage points, or wait for percentage points, any excess money spent is not returned as change.

This gives us several purchasable upgrades right off the bat:

* Percentage Points passive earning
* Minimum / Maximum chance on additive button press
* Rate of decrease of percentage on additive button press
* Minimum / Maximum chance on double button press
* Rate of decrease of percentage on double button press


Think on "Prestiging" and what "Prestiging" means in this game.
Think on potentially having different "Levels"


## TODO

* Implement GUI & Game Loop
* Implement compression on assets, even if compression doesn't save any space
* Implement Physics if necessary
* Develop with ECS in mind, Data Oriented Design
