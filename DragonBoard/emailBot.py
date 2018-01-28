import smtplib
from os.path import basename
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate

def send(msg, sender, recievers):
        username = sender
        password = "jojo123123"
                
        sender = sender
        recievers = recievers
        
        PostureMsg = MIMEText(msg, 'plain')

        msg = MIMEMultipart()
        msg["To"] = COMMASPACE.join(recievers)
        msg["From"] = sender
        msg['Date'] = formatdate(localtime=True)
        msg['Subject'] = "Posture Test"
        
        msg.attach(PostureMsg)
        
        try: 
            server = smtplib.SMTP('smtp.gmail.com:587')
            server.ehlo()
            server.starttls()
            server.login(username,password)
            server.sendmail(sender, recievers, msg.as_string())
            server.close()
            print("sent")
        except:
            print("something went wrong")

