# Econ Destroyer: DMG (Double Money Game)

This is a game that was inspired by a reddit post and those stupid clicker games that are everywhere. I kind of want to make my own stupid clicker game.

The premise of the post is that you have $1. You can choose to double your current money, or you can choose to keep the money. You have a 99.9% chance to double your money. If doubling the money fails, you don't get anything. How many times do you double your money before you choose to keep your money?

I created a small C program, a text-based game, that explored this concept. What I've found is: most of the time you are able to overflow an unsigned long, long before you fail to double your money. This question will have you crashing whatever economy you're in before you have to really consider stopping. Before creating this program, I had thought 14 Million was a good stopping point, when in reality a good stopping point would be any amount that doesn't crash the economy you're in.

With this in mind, there should be a bit more of an interesting setup for this. I'm not entirely sure what I would do differently, but this is what this new game is for.

I'll be making this game open source, with an emphasis on an honor system. If this game turns out to be good, and monetizable, I don't want anyone to make more money off of this game than I do, but keeping in line with open source, I'll let the honor system be the enforcer of this. I would also like this game to have been purchased before you play, but again, I'll rely on the honor system to enforce this. If I haven't provided any place to purchase this game, or give way for voluntary financial compensation, then that is a failure on my part, and the honor system cannot enforce anything here. The assets are free for personal use if they are not already covered by a license from a third-party.

It likely won't go anywhere, and may end up abandonware, but I'm hopeful it will at least get to a finished state.

The assets that I may or may not create are likely to be comparable to mush on the ground. I'm not so disillusioned to think differently. These assets, however, are mine. They are free for personal use.

Assets that are under any directory or sub-directory that has the name of `vendor` are not mine.

I know my code and/or cmake setup may be disastrous, I am open to feedback. I am not open to being bullied unless it's funny and good natured.

## Cloning / Running

So far this has only been tested on Ubuntu.

* `git clone --recurse-submodules -j8 git@github.com:Cragady/double-money-game.git`
  * -j can be whatever you want, or even left out
* `cd double-money-game`
* `cmake .`
* `make`
* `make run`

## Game Loop

There will be a dual-currency to a multi-currency system. The player will earn "Percentage Points" by waiting. You can use "Percentage Points" to buy one-time use to increase percentages associated with a risk in game.

You are given $1 initially. You can risk to add a set amount e.g. $0.05, $0.10, $0.25, etc. Whatever makes sense to add. There will be a decent chance to reset back to $1 if you do not accept.

You are given a chance to double your money. There is a minimum amount and maximum amount for the percentage. The percentage is decreased slowly each time the button is pushed, but never going below the minimum. If you purchase percentage points, or wait for percentage points, any excess money spent is not returned as change. Failure to double will set the money pool back to minimum.

This gives us several purchasable upgrades right off the bat:

* Percentage Points passive earning
* Minimum / Maximum chance on additive button press
* Rate of decrease of percentage on additive button press
* Minimum / Maximum chance on double button press
* Rate of decrease of percentage on double button press

Other items that could give even more purchasable upgrades:

* Additive button press amount e.g. Not $1, but a min and max here too
* Random change on additive button press amount
* Button Health - this will allow for multiple fails and upgrades that are tied to button damage on fail, and button health

* Mini-Games that will help with the main game


Think on "Prestiging" and what "Prestiging" means in this game.
Think on potentially having different "Levels"


## TODO

* Implement GUI & Game Loop
* Implement compression on assets, even if compression doesn't save any space
* Implement Physics if necessary
* Develop with ECS in mind, Data Oriented Design
