=================================
i2p-opentracker
mods and notes by zzz March 2008
=================================

SOURCE
------
This is based on the opentracker code pulled from CVS March 2008.
The most recent change in CVS as of the date pulled was Feb. 4, 2008.
See README for the CVS archive location.
The website, by the way, is http://erdgeist.org/arts/software/opentracker/ .


LICENSE
-------
opentracker is beerware, libowfat is GPL, and zzz's mods are beerware too.
No warranty, use at your own risk.


BUILDING
--------
You still need the libowfat library.
See README or just do:

	cvs -d :pserver:cvs@cvs.fefe.de:/cvs -z9 co libowfat
	cd libowfat
	make
	cd ../i2p.i2p-opentracker
	make


RUNNING
-------
	Create an HTTP server tunnel pointing to localhost port 6969
	./opentracker &
	There's no configuration, no logging, no output, nothing.
	Verify it's working by using a browser to go to http://your-tracker-name.i2p/stats
	Make a torrent in i2psnark (see below) and start itt.
	After it announces, verify with http://your-tracker-name.i2p/stats?mode=top5


TESTED/UNTESTED
---------------
Tested with i2psnark only.
Not tested with i2p-bt, i2prufus, Azureus.


I2PSNARK SETUP
--------------
If you want to create torrents for opentracker, it's easiest if you
add the tracker to your i2psnark.config.

Put the following line in i2psnark.config and restart the router (sorry about having to restart):

	i2psnark.trackers=opentracker=http://YOUR-BASE64.i2p/a=http://YOUR-NAME.i2p/stats?mode=top5,Postman=http://YRgrgTLGnbTq2aZOZDJQ~o6Uk5k6TK-OZtx0St9pb0G-5EGYURZioxqYG8AQt~LgyyI~NCj6aYWpPO-150RcEvsfgXLR~CxkkZcVpgt6pns8SRc3Bi-QSAkXpJtloapRGcQfzTtwllokbdC-aMGpeDOjYLd8b5V9Im8wdCHYy7LRFxhEtGb~RL55DA8aYOgEXcTpr6RPPywbV~Qf3q5UK55el6Kex-6VCxreUnPEe4hmTAbqZNR7Fm0hpCiHKGoToRcygafpFqDw5frLXToYiqs9d4liyVB-BcOb0ihORbo0nS3CLmAwZGvdAP8BZ7cIYE3Z9IU9D1G8JCMxWarfKX1pix~6pIA-sp1gKlL1HhYhPMxwyxvuSqx34o3BqU7vdTYwWiLpGM~zU1~j9rHL7x60pVuYaXcFQDR4-QVy26b6Pt6BlAZoFmHhPcAuWfu-SFhjyZYsqzmEmHeYdAwa~HojSbofg0TMUgESRXMw6YThK1KXWeeJVeztGTz25sL8AAAA.i2p/announce.php=http://tracker.postman.i2p/,eBook=http://E71FRom6PZNEqTN2Lr8P-sr23b7HJVC32KoGnVQjaX6zJiXwhJy2HsXob36Qmj81TYFZdewFZa9mSJ533UZgGyQkXo2ahctg82JKYZfDe5uDxAn1E9YPjxZCWJaFJh0S~UwSs~9AZ7UcauSJIoNtpxrtbmRNVFLqnkEDdLZi26TeucfOmiFmIWnVblLniWv3tG1boE9Abd-6j3FmYVrRucYuepAILYt6katmVNOk6sXmno1Eynrp~~MBuFq0Ko6~jsc2E2CRVYXDhGHEMdt-j6JUz5D7S2RIVzDRqQyAZLKJ7OdQDmI31przzmne1vOqqqLC~1xUumZVIvF~yOeJUGNjJ1Vx0J8i2BQIusn1pQJ6UCB~ZtZZLQtEb8EPVCfpeRi2ri1M5CyOuxN0V5ekmPHrYIBNevuTCRC26NP7ZS5VDgx1~NaC3A-CzJAE6f1QXi0wMI9aywNG5KGzOPifcsih8eyGyytvgLtrZtV7ykzYpPCS-rDfITncpn5hliPUAAAA.i2p/pub/bt/announce.php=http://de-ebook-archiv.i2p/pub/bt/,NickyB=http://9On6d3cZ27JjwYCtyJJbowe054d5tFnfMjv4PHsYs-EQn4Y4mk2zRixatvuAyXz2MmRfXG-NAUfhKr0KCxRNZbvHmlckYfT-WBzwwpiMAl0wDFY~Pl8cqXuhfikSG5WrqdPfDNNIBuuznS0dqaczf~OyVaoEOpvuP3qV6wKqbSSLpjOwwAaQPHjlRtNIW8-EtUZp-I0LT45HSoowp~6b7zYmpIyoATvIP~sT0g0MTrczWhbVTUZnEkZeLhOR0Duw1-IRXI2KHPbA24wLO9LdpKKUXed05RTz0QklW5ROgR6TYv7aXFufX8kC0-DaKvQ5JKG~h8lcoHvm1RCzNqVE-2aiZnO2xH08H-iCWoLNJE-Td2kT-Tsc~3QdQcnEUcL5BF-VT~QYRld2--9r0gfGl-yDrJZrlrihHGr5J7ImahelNn9PpkVp6eIyABRmJHf2iicrk3CtjeG1j9OgTSwaNmEpUpn4aN7Kx0zNLdH7z6uTgCGD9Kmh1MFYrsoNlTp4AAAA.i2p/bittorrent/announce.php=http://nickyb.i2p/bittorrent/

Or, when you create the tracker, enter the url http://YOUR-BASE64.i2p/a in the form.


CHANGES FOR I2P
---------------
Almost all the changes are in ot_http.c, trackerclient.h, and trackerclient.c.

	- Changed IP storage from 4 bytes to 520 bytes (Base64 dest + ".i2p")
	- Store and return 20 byte peer_id since i2psnark checks for a match
	- Check only the dest for a match, port and id are ignored for matching
	- So the in-memory size is 544 bytes per peer, not 8.
	- Rather than returning the (standard) list of dictionaries
	  containing (peerid, ip, port) for each peer.
	  opentracker returned a flat byte string of length 6*n.
	  Maybe that's the usual practice elsewhere, but i2psnark expects the
	  list of dictionaries. So fixed it up to do that. (trackerclient.c)
	- Don't deliver a peer's own dest to it (would hose i2psnark because it doesn't check)
	- Increase output buffer size, reduce default and max numwant
	- Changed default ip binding from 0.0.0.0 to 127.0.0.1
	- Change interval from 30m with randomization to fixed 15m (i2psnark does randomization)
	- Changed client timeout from 30s to 60s (I think)
	- Disabled UDP and ifdef'ed it out, probably wasn't worth the effort though


NOTES
-----
Since there's essentially no documentation for opentracker, here's some notes:

	- Announce url can be anything starting with "/a" or "/" - /announce.php works fine
	- Stats url is /stats
	  additional stats with /stats?mode=xxxx, modes are:
	     peer, conn, top5, scrp, torr, fscr, tcp4, udp4,
	     s24s, tpbs, herr, startstop, toraddrem, vers, busy
	  see ot_http.c for details
	- Scraping seems to work with /sc?info_hash=... but a full scrape (without ?info_hash)
	  looks to be disallowed.
	- Full scrapes are available with /scrape%20HTTP/?format={bin,ben,url,txt} ,
	  although all the formats look binary encoded to me, so maybe that isn't right.
	- Syncing disabled


POSSIBLE IMPROVEMENTS
---------------------
	- Could un-Base64 before storage to save about 128 bytes per peer
	- The timeouts in trackerlogic.h may need further adjustment - no documentation though
	  The tracker seems to forget about peers really quickly, not sure
	  exactly which timeout to tweak, or if I broke something.
	- Have it respond to HEAD requests so eepsite trackers can find it
	- Have it respond with something besides 404 Not Found to a 'home page' request,
	  e.g. "this is an open tracker, you can't store torrents here"
	- Full scrapes are pretty slow, perhaps they should be disabled...
	  on the other hand, you could make a pretty html scrape output
	  and make it be the 'home page'.
	- 'make' doesn't seem to rebuild correctly if you change a .h file - do a 'make clean' first
