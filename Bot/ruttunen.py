import discord, datetime, asyncio, random, youtube_dl

from discord import Game
from discord.ext import commands
from bs4 import BeautifulSoup
import urllib3, urllib.parse
import json as simplejson





TOKEN = 'NTAyMDI5NDcyOTM0MDAyNjg5.DqiA4A.tdtqccdZRunTpnP5deWtQQWXZ9U'


client = discord.Client()

players = {}


@client.event
async def on_message(message):
    # we do not want the bot to reply to itself
    if message.author == client.user:
        return

    if message.content.startswith('Searching'):
        await message.channel.send('NPC')


    if message.content.startswith('soitappa'):
        msg = message.content.split(' ')
        textToSearch = ''
        for i in range(1,len(msg)):
            textToSearch += msg[i] + ' '
        print(textToSearch)
        query = urllib.parse.quote(textToSearch)
        url = "https://www.youtube.com/results?search_query=" + query
        response = urllib.request.urlopen(url)
        html = response.read()
        soup = BeautifulSoup(html,features="html.parser",)
        i = 1
        videolista = []
        videonimilista = []
        for vid in soup.findAll(attrs={'class': 'yt-uix-tile-link'}):
            videolista.append('https://www.youtube.com' + vid['href'])
        for title in soup.findAll(attrs={'class': 'yt-lockup-title'}):
            videonimilista.append(title.find('a').text.strip())
        print(videonimilista)
        try:
            await message.channel.send('1 -  '+videonimilista[0] + '\n'+'2 - '+videonimilista[1] + '\n'+'3 - '+videonimilista[2] + '\n'+'4 - '+videonimilista[3] + '\n'+'5 - '+videonimilista[4] + '\n')
        except:
            await message.channel.send('1 -  ' + videonimilista[0])

        def pred(m):
            return m.author == message.author and m.channel == message.channel

        valinta = await client.wait_for('message', check = pred)
        numero = valinta.content

        channel = message.author.voice.channel
        await channel.connect()
        server = message.server
        voice_client = client.voice_client_in(server)
        beforeArgs = "-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 5"
        ytArgs = "-i --no-playlist"

        try:
            player = await voice_client.create_ytdl_player(videolista[int(numero)-1], ytdl_options = ytArgs, before_options = beforeArgs)
            players[server.id] = player
            player.start()

        except:
            await client.send_message(message.channel, 'Ei kykene')

    if message.content.startswith('lopeta'):
        id = message.server.id
        players[id].stop()

    if message.content.startswith('ootappa'):
        id = message.server.id
        players[id].pause()

    if message.content.startswith('jatka'):
        id = message.server.id
        players[id].resume()



    if message.content.startswith('jogiin'):
        print('jogiin')
        await message.channel.send('jogiin', file = discord.File('jogiin.png'))

    if message.content.startswith('kolikko'):
        await client.send_message(message.channel,random.choice(['kruuna','klaava']))

    if message.content.startswith('mies'):
        mies = discord.utils.get(message.server.emojis, name="mies")
        await client.add_reaction(await client.send_message(message.channel,mies),mies)

    if message.content.startswith('robo kerro tarina'):
        pastalista = ['helvetin_perkele.txt']
        tiedosto = random.choice(pastalista)
        f = open(tiedosto,"r")
        for i in f:
            vastaus = i;
            await client.send_message(message.channel,vastaus)
        f.close()


    if message.content.startswith('kps'):
        await client.send_message(message.channel, ' valitse k/p/s')
        msg = await client.wait_for_message(author=message.author)
        yritys = msg.content
        vastaus = random.choice(['k','p','s'])
        if vastaus == 'k' and yritys == 's':
            await client.send_message(message.channel,'kivi')
            await client.send_message(message.channel,'oot paskaa')

        elif vastaus == 'k' and yritys == 'p':
            await client.send_message(message.channel, 'kivi')
            await client.send_message(message.channel, 'no vittu')

        elif vastaus == 's' and yritys == 'p':
            await client.send_message(message.channel, 'sakset')
            await client.send_message(message.channel, 'haha')

        elif vastaus == 's' and yritys == 'k':
            await client.send_message(message.channel, 'sakset')
            await client.send_message(message.channel, 'kys')

        elif vastaus == 'p' and yritys == 'k':
            await client.send_message(message.channel, 'paperi')
            await client.send_message(message.channel, 'sut on servattu vitun kersa')

        elif vastaus == 'p' and yritys == 's':
            await client.send_message(message.channel, 'paperi')
            await client.send_message(message.channel, 'justiisa')

        elif vastaus == yritys:
            await client.send_message(message.channel,'meil samat')
            await client.send_message(message.channel, 'noo, ei voi mittään')
            await client.send_message(message.channel,'pittää yrittää jonkun ajan päästä uuvestaan')


    if message.content.startswith('2222'):
        aika = datetime.datetime
        if aika.now().hour == 22:
            if aika.now().minute < 22:
                msg = 'Kakkosiin aikaa '+ str(22-aika.now().minute) + ' minuuttia.'
            elif aika.now().minute == 22:
                msg = '2222 the tradition continues'
            else:
                msg = 'Kakkosiin aikaa 23 tuntia ja ' + str(82 - aika.now().minute) + ' minuuttia.'
        elif 23 <= aika.now().hour <= 24:
            if aika.now().minute < 22:
                msg = 'Kakkosiin aikaa ' + str(46 - aika.now().hour) + ' tuntia ja ' + str(22 - aika.now().minute) + ' minuuttia.'
            else:
                msg = 'Kakkosiin aikaa ' + str(45 - aika.now().hour) + ' tuntia ja ' + str(82 - aika.now().minute) + ' minuuttia.'

        elif aika.now().hour != 22:
            if aika.now().minute < 22:
                msg = 'Kakkosiin aikaa ' + str(22 - aika.now().hour) + ' tuntia ja ' + str(22 - aika.now().minute) + ' minuuttia.'
            else:
                msg = 'Kakkosiin aikaa ' + str(21 - aika.now().hour) + ' tuntia ja ' + str(82 - aika.now().minute) + ' minuuttia.'

        await message.channel.send(msg)

    if message.content.startswith('terve'):
        if message.author.id == '185377419987910656':
            msg = 'Terve, isäntä.'
        else:
            msg = 'Terve {0.author.mention}'.format(message)
        await client.send_message(message.channel, msg)

    if message.content.startswith('whomdoyouserve'):
        await client.send_message(message.channel,random.choice(['JOONA!','SARUMAN!','ISRAEL!']))

    if message.content.startswith('noppa'):
        try:
            args = message.content.split(' ')
            määrä = int(args[1])
            lista = range(1,määrä+1)
            await client.send_message(message.channel,str(random.choice(lista)))
        except:
            await client.send_message(message.channel,'Käyttö: !noppa sivujen lkm')


    if message.content.startswith('!remindme'):

        try:
            args = message.content.split(' ')
            aika = int(args[2])
            syy = args[1]
            msg = 'Muistutan asiasta' + ' ' + args[1] + ' ' + args[2] + ' min kuluttua.'
            await client.send_message(message.channel, msg)
            await asyncio.sleep(aika*60)
            msg = args[1]
            await client.send_message(message.author, msg)
        except:

            await client.send_message(message.channel, 'käyttö: !remindme asia minuutit')




@client.event
async def on_ready():
    await client.change_presence(activity = discord.Activity(name='Vuosihuolto'))
    channel = client.get_channel(490651251244138498)§
    await channel.send('Tästä se menee päälle')
    print('Logged in as')
    print(client.user.name)
    print(client.user.id)
    print(datetime.datetime.now())
    print('------')


client.run(TOKEN)