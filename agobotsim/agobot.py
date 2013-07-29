'''
Created on Jul 23, 2013

@author: t-ruzha
'''

import irc.bot
import random
import threading

class Agobot(irc.bot.SingleServerIRCBot):
    def __init__(self, server, port=6667):
        self.id = random.randint(0, 2**32-1)
        self.nick = "bot_{:08x}".format(self.id)
        irc.bot.SingleServerIRCBot.__init__(self, [(server, port)], self.nick, self.nick, 5)
        self.channel = "#Agonet"
        print("Agobot [%s] joined channel [%s] on [%s:%d]" % (self.nick, self.channel, server, port))
        
    def on_welcome(self, c, e):
        c.join(self.channel)
        
    def on_privmsg(self, c, e):
        self.do_command(e, e.arguments[0])
        
    def on_pubmsg(self, c, e):
        a = e.arguments[0].split(":", 1)
        if len(a) > 1 and (a[0] == "" or a[0].lower() == self.connection.get_nickname().lower()):
            self.do_command(e, a[1].strip())
        
    def do_command(self, e, cmd):
        nick = e.source.nick
        c = self.connection
        print("{0}: command from {1}: {2}".format(self.connection.get_nickname(), nick, cmd))
        
        if cmd == "disconnect":
            self.disconnect()
        elif cmd == "die":
            self.die()
        elif cmd == "hi":
            c.notice(nick, "Hi")
        elif cmd == "stats":
            for chname, chobj in self.channels.items():
                c.notice(nick, "--- Channel statistics ---")
                c.notice(nick, "Channel: " + chname)
                users = chobj.users()
                #users.sort()
                c.notice(nick, "Users: " + ", ".join(users))
                opers = chobj.opers()
                #opers.sort()
                c.notice(nick, "Opers: " + ", ".join(opers))
                voiced = chobj.voiced()
                #voiced.sort()
                c.notice(nick, "Voiced: " + ", ".join(voiced))
        else:
            c.notice(nick, "Not understood: " + cmd)
            
class AgobotThread(threading.Thread):
    def __init__(self, server, port=6667):
        threading.Thread.__init__(self)
        self.bot = Agobot(server, port)
        
    def run(self):
        print("Running bot", self.bot.nick)
        self.bot.start()









