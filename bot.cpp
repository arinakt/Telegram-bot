# -*- coding: utf-8 -*- import telebot import requests import sqlite3 as lite 
import sys import logging import time import os reload(sys) import os.path sys.setdefaultencoding('utf8') from telebot import types import botan 
from datetime import datetime, timedelta, date, time as dt_time 
  
subfile='/mnt/files/s_sub.txt'; banfile='/mnt/files/shameban.txt' 
ex = [line.rstrip('\n') for line in open(banfile,'rt')] 
  
sub = [line.rstrip('\n') for line in open(subfile,'rt')] 
adminid='��� ��!' bd='/mnt/files/test.db' API_TOKEN = '' botan_key = '' 
bot = telebot.TeleBot(API_TOKEN) bot.send_message(adminid,"� ����������" ) 
logger = telebot.logger 
telebot.logger.setLevel(logging.DEBUG) 
  
  
markup = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) markup2 = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) markup3 = types.ReplyKeyboardMarkup(row_width=2,resize_keyboard=True) markup_h = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) markup_h.add('','','','','\xF0\x9F\x8D\x80 �������','', '\xF0\x9F\x93\x9D ����������','\xF0\x9F\x94\x99 �����' ) markup_f = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) markup_f.add('','','','','\xF0\x9F\x8D\x80 ����','', '','\xF0\x9F\x94\x99 �����' ) 
markup2.add('\xE2\x9D\xA4 ��� 5 ����','\xE2\x9D\xA4 ��� 5 �������','','', '\xF0\x9F\x93\x9D ����������') markup3.add('������') 
markup_start = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) 
markup_start.add('\xF0\x9F\x8E\xA8 ����','\xF0\x9F\x93\x9D �������','','����������','\xF0\x9F\x93\x88 ����������') 
markup_start_ne = types.ReplyKeyboardMarkup(row_width=3,resize_keyboard=True) markup_start_ne.add('\xF0\x9F\x8E\xA8 ����','\xF0\x9F\x93\x9D 
�������','','�����������','\xF0\x9F\x93\x88 ����������') 
  
  
  
  
@bot.message_handler(commands=['unsubscribe','Stop','stop','off','OFF','Off']) def send_welcome(message): 
     os.system('sed -i "/'+str(message.chat.id)+'/d" "/mnt/files/s_sub.txt"') 
     bot.send_message(message.chat.id,"�������� ��������! (", reply_markup=markup)      botan.track(botan_key, message.chat.id, message, '�������� �����������', reply_markup=markup_start_ne) 
 	  
 	  
 	  
@bot.message_handler(commands=['subscribe']) def send_welcome(message): 
     
    
    global sub     sub = [line.rstrip('\n') for line in open(subfile,'rt')]     if str(message.chat.id) not in sub: 
        
         with open(subfile, 'a') as f: 
                   f.write(str(message.chat.id)+"\n")          sub = [line.rstrip('\n') for line in open(subfile,'rt')] 
         bot.send_message(message.chat.id,"�������� ���������, ��� ���������� �������������� ��������� /unsubscribe", reply_markup=markup_start) 
         botan.track(botan_key, message.chat.id, message, '�������� ���������')          bot.send_message(adminid,"�������� ���������")     else: 
        bot.send_message(message.chat.id,"�������� ��� ���������. ��� ���������� �������������� ��������� /unsubscribe", reply_markup=markup_start)  
  
 	 	 
@bot.message_handler(commands=['help', 'start']) def send_welcome(message): 
    global sub 
    sub = [line.rstrip('\n') for line in open(subfile,'rt')] 
     
    
    if str(message.chat.id) not in sub: 
        
          bot.send_message(message.chat.id,"����� ���������� � ��� ��������� �������! �������� ����  ������� ��������! \n ���������� ����, ������� ������!\n ������ ������: \n /photo - ��������� ���� \n /story - ��������� ������� \n  \n  /subscribe - �������� �� ������� � ����!!! \n /help - ������   \n��� ���������� ������� - �������� ���� ��� �������!!!  \n ��� ����� � ������� ������ �������� ��������� � ���.", reply_markup=markup_start_ne)     else: 
      bot.send_message(message.chat.id,"����� ���������� � ��� ��������� �������! �������� ����  ������� ��������! \n ���������� ����, ������� ������!\n ������ ������: \n /photo - ��������� ���� \n /story - ��������� ������� \n  \n  /subscribe - �������� �� ������� � ����!!! \n /help - ������   \n��� ���������� ������� - �������� ���� ��� �������!!!  \n ��� ����� � ������� ������ �������� ��������� � ���.", reply_markup=markup_start) 
     
    botan.track(botan_key, message.chat.id, message, '����� ����������!') @bot.message_handler(commands=['off', 'stop','Stop','Off','OFF']) def send_off(message): 
     
  
     os.system('sed -i "/'+str(message.chat.id)+'/d" '+subfile) 
     bot.send_message(message.chat.id,"�������� ��������! (", reply_markup=markup_start_ne)      botan.track(botan_key, message.chat.id, message, '�������� �����������') 
 	  
    
  
@bot.message_handler(content_types=['photo']) def handle_docs_photo(message):    try:         global ex  
       
       chat_id = message.chat.id        keyboard = types.InlineKeyboardMarkup(row_width=4)         if str(message.chat.id) not in ex:         file_info = bot.get_file(message.photo[len(message.photo)-1].file_id)         downloaded_file = bot.download_file(file_info.file_path) 
       
        pa='/mnt/files/bot/'+str(file_info.file_path);         with open(pa, 'wb') as new_file:            new_file.write(downloaded_file) 
         
         
 	 
        con=lite.connect(bd, timeout=10) 
        cur=con.cursor() 
        cur.execute('INSERT INTO photo (id, cid, text,rating,be,fu) VALUES(NULL, 
"'+str(message.chat.id)+'","'+pa+'","0","0","0")')         con.commit()         id=cur.lastrowid; 
        con.close 
         
         
        bot.reply_to(message, "������� :)") 
       
        img = open(pa, 'rb') 
        callback_bad = types.InlineKeyboardButton(text="�������", callback_data=pa)         callback_button = types.InlineKeyboardButton(text="������", callback_data='bad[!!!]'+str(chat_id)) 
        callback_ban = types.InlineKeyboardButton(text="���", callback_data='ban[!!!]'+str(chat_id))         callback_send_story = types.InlineKeyboardButton(text="��������", callback_data='sendphoto[!!!]'+str(id)) 
          
        keyboard.add(callback_button,callback_bad,callback_send_story,callback_ban) 
             
         
        bot.send_photo(adminid, img,reply_markup=keyboard) 
    
   except Exception as e: 
        bot.send_message(adminid,e )  
  
  
 	 	 
@bot.callback_query_handler(func=lambda call: True) def callback_inline(call): 
    global ex     if call.message:         print(call.message)         if '/mnt/files/bot/photo/' in call.data: 
                     try: 
            
            os.remove(call.data) 
            con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            con.execute('DELETE from photo where text="'+call.data+'";') 
  
            con.commit()             con.close 
            bot.answer_callback_query(callback_query_id=call.id, show_alert=False, text=" �������:"+str(con.total_changes)) 
            bot.edit_message_caption(chat_id=call.message.chat.id, message_id=call.message.message_id, caption="������") 
             
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'lf[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE photo SET rating = rating + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close 
            bot.edit_message_caption(chat_id=call.message.chat.id, message_id=call.message.message_id, caption="\xF0\x9F\x98\x88") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)          elif 'nf[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE photo SET be = be + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close 
            bot.edit_message_caption(chat_id=call.message.chat.id, message_id=call.message.message_id, caption="\xF0\x9F\x98\x87") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'ff[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE photo SET fu = fu + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close 
            bot.edit_message_caption(chat_id=call.message.chat.id, message_id=call.message.message_id, caption="\xF0\x9F\x98\xA1") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'ls[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE story SET rating = rating + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close 
            bot.edit_message_text(chat_id=call.message.chat.id, message_id=call.message.message_id, text=call.message.text+" +\xF0\x9F\x98\x88") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)          elif 'ns[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE story SET be = be + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close             bot.edit_message_text(chat_id=call.message.chat.id, message_id=call.message.message_id, text=call.message.text+" +\xF0\x9F\x98\x87") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'fs[!!!]' in call.data: 
                       try: 
            words = call.data.split("[!!!]")  
             
             
            con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute("""UPDATE story SET fu = fu + 1  WHERE id="""+str(words[1])+"""  """) 
           
            con.commit()             con.close 
            bot.edit_message_text(chat_id=call.message.chat.id, message_id=call.message.message_id, text=call.message.text+" +\xF0\x9F\x98\xA1") 
            
             
            
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'story[!!!]' in call.data: 
                      try: 
            words = call.data.split("[!!!]")              con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            con.execute('DELETE from story where id="'+words[1]+'";') 
  
            con.commit()             con.close 
            bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text="�������:"+str(con.total_changes)) 
            bot.edit_message_text(chat_id=call.message.chat.id, message_id=call.message.message_id, caption="������")            except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'bad[!!!]' in call.data: 
                       try: 
            img = open('/mnt/files/bot/bad.jpeg', 'rb') 
            words = call.data.split("[!!!]")  
            bot.send_photo(words[1], img,"", reply_markup=markup_h) 
           
           
           except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)         elif 'ban[!!!]' in call.data: 
                       try: 
words = call.data.split("[!!!]")  
 
 
            with open(banfile, 'a') as f: 
                   f.write(str(words[1])+"\n") 
             
            ex = [line.rstrip('\n') for line in open(banfile,'rt')] 
            bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text="�������� ������������: ["+str(words[1])+"]")            except Exception as e: 
             bot.answer_callback_query(callback_query_id=call.id, show_alert=True, text=e)          elif 'sendtext[!!!]' in call.data:            i=0;            try: 
             
            words = call.data.split("[!!!]")             con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute('SELECT * FROM story where id='+words[1]+' ORDER BY RANDOM() LIMIT 1')             data = cur.fetchone() 
           
                 
           
            con.close 
            sub = [line.rstrip('\n') for line in open(subfile,'rt')]             keyboard = types.InlineKeyboardMarkup(row_width=3) 
            callback_shame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x88 ������', callback_data='ls[!!!]'+str(data[0])) 
            callback_nshame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x87 ������', callback_data='ns[!!!]'+str(data[0])) 
            callback_fuu = types.InlineKeyboardButton(text='\xF0\x9F\x98\xA1 ��!', callback_data='fs[!!!]'+str(data[0]))   
            keyboard.add(callback_shame,callback_nshame,callback_fuu)   
             
            for line in sub: 
                           try: 
              i=i+1;               if  (i % 10 ==0 ):                time.sleep(1)  
              m="#"+str(data[0])+"\n"+data[2]+"\n\n"+'\xF0\x9F\x98\x88 '+str(data[3])+ ' 
\xF0\x9F\x98\x87 '+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5]);               msg = bot.send_message(line,m, reply_markup=keyboard)    
              bot.register_next_step_handler(msg, lambda m: process_rating(m,data[0],line)) 
              
             except Exception as e: 
                             pass 
               
             
             
             
             
           except Exception as e: 
             pass         elif 'sendphoto[!!!]' in call.data:            i=0 
           try: 
             
            words = call.data.split("[!!!]")             con=lite.connect(bd, timeout=10)             cur=con.cursor() 
            cur.execute('SELECT * FROM photo where id='+words[1]+' ORDER BY RANDOM() LIMIT 1')             data = cur.fetchone() 
           
                 
                
            con.close 
            sub = [line.rstrip('\n') for line in open(subfile,'rt')] 
               
            keyboard = types.InlineKeyboardMarkup(row_width=3) 
            callback_shame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x88 ������', callback_data='lf[!!!]'+str(data[0])) 
            callback_nshame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x87 ������', callback_data='nf[!!!]'+str(data[0])) 
            callback_fuu = types.InlineKeyboardButton(text='\xF0\x9F\x98\xA1 ��!', callback_data='ff[!!!]'+str(data[0]))              keyboard.add(callback_shame,callback_nshame,callback_fuu)             for line in sub: 
                          try: 
               i=i+1                if  (i % 10 ==0 ):                  time.sleep(1)                img = open(data[2], 'rb') 
               m="#"+str(data[0])+"\n"+data[2]+"\n\n"+'\xF0\x9F\x98\x88 '+str(data[3])+ ' 
\xF0\x9F\x98\x87 '+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5]) 
               msg =bot.send_photo(line, img,'\xF0\x9F\x98\x88 '+str(data[3])+ ' \xF0\x9F\x98\x87 
'+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5]), reply_markup=keyboard)                   bot.register_next_step_handler(msg, lambda m: process_rating_p(m,data[0],line))              except Exception as e: 
               pass 
               
             
             
             
             
           except Exception as e: 
             pass  def process_add(message):    try:        global ex  
        
       chat_id = message.chat.id 
       text = message.text 
  
       if (text in "������"): 
        bot.reply_to(message,"����� � ��������� ��� )", reply_markup=markup_h)         return        if str(message.chat.id) not in ex:         if len(text)>30 and (len(text)<1001): 
            text=text.replace('\"', ' ') text=text.replace('\'', ' ') text=text.replace('.http://', ' ') 
text=text.replace('.www', ' ')             text=text.replace('.ru', ' ')             text=text.replace('.com', ' ')             text=text.replace('.org', ' ')             text=text.replace('.org', ' ')             con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute('INSERT INTO story (id, cid, text,rating,be,fu) VALUES(NULL, 
"'+str(chat_id)+'","'+text+'","0","0","0")') 
            con.commit()             id=cur.lastrowid; 
            con.close 
             
            
            bot.reply_to(message, "������� :)") 
            
            keyboard = types.InlineKeyboardMarkup(row_width=4) 
            callback_bad = types.InlineKeyboardButton(text="�������", callback_data='story[!!!]'+str(id))             callback_button = types.InlineKeyboardButton(text="������", callback_data='bad[!!!]'+str(chat_id)) 
            callback_ban = types.InlineKeyboardButton(text="���", callback_data='bad[!!!]'+str(chat_id))             callback_send_story = types.InlineKeyboardButton(text="��������", callback_data='sendtext[!!!]'+str(id)) 
          
            keyboard.add(callback_button,callback_bad,callback_send_story,callback_ban) 
             
            bot.send_message(adminid,"�������: ["+str(chat_id)+"] "+text, reply_markup=keyboard) 
  
          
        else: 
             bot.reply_to(message, '������� ������ ���� �� ����� 20 �������� � �� ����� 1000')    except Exception as e:           bot.send_message(adminid,e ) def process_banuser(message):         try: 
            global ex 
            chat_id = message.chat.id             text = message.text             with open(banfile, 'a') as f:                    f.write(str(text)+"\n") 
            
            ex = [line.rstrip('\n') for line in open(banfile,'rt')] 
         
        except Exception as e: 
              bot.reply_to(message,e) 
  
 	 	 	   
def process_rating(message,text,ch):     try: 
        
        rating = message.text         id=rating.replace('#', '')         id=id.replace(' ', '')         id = rating.split('\n')         print str(rating) 
        if (unicode(rating)== '\xF0\x9F\x98\x88 ������'): 
            con=lite.connect(bd)             cur=con.cursor() 
            cur.execute("""UPDATE story SET rating = rating + 1  WHERE id="""+str(text)+"""  """)             botan.track(botan_key, message.chat.id, message, '������� ������')             con.commit() 
            con.close 
            bot.send_message(ch,'\xF0\x9F\x98\x88') 
 	 	 	 
        elif (rating== '\xF0\x9F\x98\x87 ������'):             con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute("""UPDATE story SET be = be + 1  WHERE id="""+str(text)+"""  """)             botan.track(botan_key, message.chat.id, message, ',������� ������')             con.commit()             con.close 
            bot.send_message(ch,'\xF0\x9F\x98\x87', reply_markup=markup)         elif (rating== '\xF0\x9F\x98\xA1 ��!'): 
            con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute("""UPDATE story SET fu = fu + 1  WHERE id="""+str(text)+"""  """)             botan.track(botan_key, message.chat.id, message, '������� ���')             con.commit() 
            con.close 
            bot.send_message(ch,'\xF0\x9F\x98\xA1')     except Exception as e: 
            bot.send_message(adminid,e )    	 def process_rating_p(message,text,ch):     try: 
        
        rating = message.text         id=rating.replace('#', '')         id=id.replace(' ', '')         id = rating.split('\n')         print str(rating)         if (unicode(rating)== '\xF0\x9F\x98\x88 ������'): 
            con=lite.connect(bd)             cur=con.cursor() 
            cur.execute("""UPDATE photo SET rating = rating + 1  WHERE id="""+str(text)+"""  """)             botan.track(botan_key, message.chat.id, message, '������� ������')             con.commit()             con.close 
            bot.send_message(ch,'\xF0\x9F\x98\x88') 
 	 	 	 
        elif (rating== '\xF0\x9F\x98\x87 ������'):             con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute("""UPDATE photo SET be = be + 1  WHERE id="""+str(text)+"""  """)             botan.track(botan_key, message.chat.id, message, ',������� ������')             con.commit() 
            con.close 
            bot.send_message(ch,'\xF0\x9F\x98\x87')         elif (rating== '\xF0\x9F\x98\xA1 ��!'): 
            con=lite.connect(bd, timeout=10) 
            cur=con.cursor() cur.execute("""UPDATE photo SET fu = fu + 1  WHERE id="""+str(text)+"""  """) botan.track(botan_key, message.chat.id, message, '������� ���') con.commit()             con.close 
            bot.send_message(ch,'\xF0\x9F\x98\xA1')     except Exception as e:           bot.send_message(adminid,e )      def process_send(message):         try: 
           con=lite.connect(bd, timeout=10) 
           cur=con.cursor()            cur.execute('SELECT DISTINCT cid FROM story')            for row in cur: 
                
               img = open('/mnt/files/bot/send/'+message.text, 'rb')                bot.send_photo(row[0], img) 
           con.close 
         
        except Exception as e:               bot.reply_to(message, e)# Handle all other messages with content_type 'text' (content_types defaults to ['text']) def process_say(message):         try: 
            words = message.text.split(",")              bot.send_message(words[0], words[1]) 
         
        except Exception as e:               bot.reply_to(message, e)# Handle all other messages with content_type 'text' (content_types defaults to ['text']) 
@bot.message_handler(func=lambda message: True) def echo_message(message): 
  
 try:     global ex 
   
    global sub 
    chat_id=message.chat.id 
    
    if (str(message.chat.id) in ex): 
       bot.reply_to(message, """�� ������ � ��� ((  ��������� ������""")        botan.track(botan_key, message.chat.id, message, '��������� �� ����') 
    
 	      else:         if (message.text in "�����������"): 
         sub = [line.rstrip('\n') for line in open(subfile,'rt')]          if str(message.chat.id) not in sub:              with open(subfile, 'a') as f: 
                   f.write(str(message.chat.id)+"\n") 
         
         bot.send_message(message.chat.id,"�������� ���������, ��� ���������� �������������� ��������� /unsubscribe", reply_markup=markup_start) 
         botan.track(botan_key, message.chat.id, message, '�������� ���������') 
          
  
       
        elif (message.text in "����������"): 
         os.system('sed -i "/'+str(message.chat.id)+'/d" '+subfile) 
         bot.send_message(message.chat.id,"�������� ��������! (", reply_markup=markup_start_ne)          botan.track(botan_key, message.chat.id, message, '�������� �����������')         elif (message.text in '\xF0\x9F\x93\x9D ����������')and (len(message.text)>4):           msg = bot.reply_to(message, """���������� ��� ���������?""", reply_markup=markup3)              bot.register_next_step_handler(msg, process_add)         elif ((message.text in "\xF0\x9F\x94\x99 �����")  and (len(message.text)>3)): 
           sub = [line.rstrip('\n') for line in open(subfile,'rt')]            if str(message.chat.id) not in sub:    
            bot.send_message(chat_id, '\xF0\x9F\x91\x87',reply_markup=markup_start_ne)            else: 
             bot.send_message(chat_id, '\xF0\x9F\x91\x87',reply_markup=markup_start)         elif (message.text== u'������'):  
            bot.reply_to(message, """��������""", reply_markup=markup_h) 
        
  
         
        
        elif ((message.text in  '\xF0\x9F\x8D\x80 �������')  or (message.text in "/story")) and (len(message.text)>4): 
            bot.send_chat_action(message.chat.id, 'typing')             con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute('SELECT * FROM story ORDER BY RANDOM() LIMIT 1')             data = cur.fetchone()             if (str(chat_id)==adminid) : 
              admin="\n ������������:"+str(data[1])             else: 
                 admin="" 	 	 
            m="#"+str(data[0])+"\n"+data[2]+"\n\n"+'\xF0\x9F\x98\x88 '+str(data[3])+ ' 
\xF0\x9F\x98\x87 '+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5])             keyboard = types.InlineKeyboardMarkup(row_width=3) 
            callback_shame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x88 ������', callback_data='ls[!!!]'+str(data[0])) 
            callback_nshame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x87 ������', callback_data='ns[!!!]'+str(data[0])) 
            callback_fuu = types.InlineKeyboardButton(text='\xF0\x9F\x98\xA1 ��!', callback_data='fs[!!!]'+str(data[0]))  
            keyboard.add(callback_shame,callback_nshame,callback_fuu) 
              
            if  (data[0] % 15 ==0 ): 
              star = types.InlineKeyboardButton(text='\xE2\xAD\x90 \xE2\xAD\x90 \xE2\xAD\x90 
\xE2\xAD\x90 \xE2\xAD\x90', url='https://telegram.me/storebot?start=yourshamebot')               keyboard.add(star)             if  (data[0] % 5 ==0 ): 
              start = types.InlineKeyboardButton(text='�������: �������� ����', url='http://telegram.me/tyhumor') 
              keyboard.add(start) 
            bot.send_message(chat_id,m, reply_markup=keyboard) 
  
            con.close 
            botan.track(botan_key, message.chat.id, message, '�������') 
            
           	 
        elif (message.text in "\xF0\x9F\x93\x9D �������"): 
bot.send_message(message.chat.id,'\xF0\x9F\x91\x87', reply_markup=markup_h) 
        elif (message.text in "\xF0\x9F\x8E\xA8 ����"):             bot.send_message(message.chat.id,'\xF0\x9F\x91\x87', reply_markup=markup_f)         elif ((message.text in "\xF0\x9F\x8D\x80 ���� /photo foto fotka ����")  and (len(message.text)>3)): 
            bot.send_chat_action(message.chat.id, 'upload_photo')             con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute('SELECT * FROM photo ORDER BY RANDOM() LIMIT 1')             data = cur.fetchone() 
             
                       
            con.close             if (os.path.exists(data[2])):              img = open(data[2], 'rb') 
             m="#"+str(data[0])+"\n"+data[2]+"\n\n"+'\xF0\x9F\x98\x88 '+str(data[3])+ ' 
\xF0\x9F\x98\x87 '+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5]);              keyboard = types.InlineKeyboardMarkup(row_width=3) 
             callback_shame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x88 ������', callback_data='lf[!!!]'+str(data[0])) 
             callback_nshame = types.InlineKeyboardButton(text='\xF0\x9F\x98\x87 ������', callback_data='nf[!!!]'+str(data[0])) 
             callback_fuu = types.InlineKeyboardButton(text='\xF0\x9F\x98\xA1 ��!', callback_data='ff[!!!]'+str(data[0]))  
             keyboard.add(callback_shame,callback_nshame,callback_fuu) 
              
             if  (data[0] % 15 ==0 ): 
              star = types.InlineKeyboardButton(text='\xE2\xAD\x90 \xE2\xAD\x90 \xE2\xAD\x90 
\xE2\xAD\x90 \xE2\xAD\x90', url='https://telegram.me/storebot?start=yourshamebot')               keyboard.add(star)              if  (data[0] % 5 ==0 ): 
              start = types.InlineKeyboardButton(text='�������: �������� ����', url='http://telegram.me/tyhumor') 
              keyboard.add(start) 
             msg =bot.send_photo(message.chat.id, img,'\xF0\x9F\x98\x88 '+str(data[3])+ ' 
\xF0\x9F\x98\x87 '+str(data[4])+' \xF0\x9F\x98\xA1 '+str(data[5]), reply_markup=keyboard)                 bot.register_next_step_handler(msg, lambda m: process_rating_p(m,data[0],message.chat.id)) 
             
             botan.track(botan_key, message.chat.id, message, '����')             else: 
                 con=lite.connect(bd, timeout=10) 
                 cur=con.cursor() 
                 con.execute('DELETE from photo where ID="'+str(data[0])+'";') 
  
                 con.commit()                  con.close 
                 bot.send_message(adminid, "�� ������� �����! ������� ������: "+str(con.total_changes)) 
                  
        elif (message.text in '\xF0\x9F\x93\x88 ����������'):             con=lite.connect(bd, timeout=10) 
            cur=con.cursor()             cur2=con.cursor()             cur3=con.cursor()             cur4=con.cursor()             cur5=con.cursor() cur6=con.cursor()             cur7=con.cursor()             cur8=con.cursor()             cur9=con.cursor()             cur10=con.cursor()             cur.execute('SELECT count(id) FROM story')             cur2.execute('SELECT count(id) FROM photo')             cur3.execute('SELECT count(id) FROM story where cid='+str(chat_id))             cur4.execute('SELECT count(id) FROM photo where cid='+str(chat_id))             cur5.execute('SELECT SUM(rating) FROM photo where cid='+str(chat_id))             cur6.execute('SELECT SUM(be) FROM photo where cid='+str(chat_id))             cur7.execute('SELECT SUM(fu) FROM photo where cid='+str(chat_id))             cur8.execute('SELECT SUM(rating) FROM story where cid='+str(chat_id))             cur9.execute('SELECT SUM(fu) FROM story where cid='+str(chat_id))             cur10.execute('SELECT SUM(fu) FROM story where cid='+str(chat_id))             story = cur.fetchall()             photo = cur2.fetchall()             mstory =cur3.fetchall()             mphoto =cur4.fetchall()              mpr =cur5.fetchall()              mpb =cur6.fetchall()             mpf =cur7.fetchall()             msr =cur8.fetchall()              msb =cur9.fetchall() 
            msf =cur10.fetchall()             con.close; 	 
            m="����������: \n ����� �������: "+str(story[0][0])+"\n ����� ����: "+ 
str(photo[0][0])+"\n\n ��� �������: "+ str(mstory[0][0])+'\n \xF0\x9F\x98\x88 '+str(msr[0][0])+ 
' \xF0\x9F\x98\x87 '+str(msb[0][0])+' \xF0\x9F\x98\xA1 '+str(msf[0][0])+  "   \n\n ��� ����:"+str(mphoto[0][0])+'\n \xF0\x9F\x98\x88 '+str(mpr[0][0])+ ' \xF0\x9F\x98\x87 
'+str(mpb[0][0])+' \xF0\x9F\x98\xA1 '+str(mpf[0][0])             bot.send_message(chat_id,m) 
         
        elif (message.text== u'b') and(str(chat_id)==adminid) :             msg = bot.reply_to(message, """��� ���� � ���? """)               bot.register_next_step_handler(msg, process_banuser) 	   
         
        elif (message.text== u'fixphoto') and(str(chat_id)==adminid) :             msg = bot.reply_to(message, """�������� ������� """)               con=lite.connect(bd, timeout=10) 
            cur=con.cursor() 
            cur.execute('SELECT * FROM photo ORDER BY RANDOM()') 
            
            for row in cur:                if (not os.path.exists(str(row[2]))): 
                con.execute('DELETE from photo where ID="'+str(row[0])+'";')             con.commit()             con.close 
            bot.send_message(adminid, "���������: "+str(con.total_changes))             ex = [line.rstrip('\n') for line in open(banfile,'rt')] 
           
        
        
        else: 
           if ((unicode(message.text)!= '\xF0\x9F\x98\x87 ������') and (unicode(message.text)!= '\xF0\x9F\x98\x88 ������')and (unicode(message.text)!= '\xF0\x9F\x98\xA1 ��!')): 
 bot.send_message(adminid,str(message.chat.id)+": " +message.text ) 
 except Exception as e: 
        bot.reply_to(message, e)        
bot.polling(none_stop=True, interval=0, timeout=3) 




