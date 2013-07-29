#! /usr/bin/env python
#
# Example program using irc.bot.
#
# Joel Rosdahl <joel@rosdahl.net>

"""A simple example bot.

This is an example bot that uses the SingleServerIRCBot class from
irc.bot.  The bot enters a channel and listens for commands in
private messages and channel traffic.  Commands in channel messages
are given by prefixing the text by the bot name followed by a colon.
It also responds to DCC CHAT invitations and echos data sent in such
sessions.

The known commands are:

    stats -- Prints some channel information.

    disconnect -- Disconnect the bot.  The bot will try to reconnect
                  after 60 seconds.

    die -- Let the bot cease to exist.

    dcc -- Let the bot invite you to a DCC CHAT connection.
"""

import irc.logging
from agobot import AgobotThread
import time
import argparse

def main():
    parser = argparse.ArgumentParser(description="Agobot Simulator")
    irc.logging.add_arguments(parser)
    args = parser.parse_args()
    irc.logging.setup(args)
    
    bots = [AgobotThread("localhost") for i in range(32)]
    for bot in bots:
        bot.start()
        time.sleep(0.1)
    
    #bot = Agobot("localhost")
    #bot.start()

if __name__ == "__main__":
    main()
