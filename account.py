def askInp(conn,type,message='',secure=False,):
    if secure == False:
        conn.send("secInp".encode())
        data = conn.recv(124)
        return data.decode('utf-8')
    else:
        conn.send("inp".encode())
        data = conn.recv(124)
        return data.decode('utf-8')

def loginInit(conn):
    account = askInp(conn,"int","0-Login\n1-SignUp\n2-PassRecover")
    return login(int(account),conn)

def login(account,conn):
    if account == 0:
        userN = askInp(conn,"inp","UserName")
        passW = askInp(conn,"pass","Password",secure=True)
    elif account == 1:
        userN = askInp(conn,"inp","UserName")
        passW = askInp(conn,"pass","Password",secure=True)
        passWConf = askInp(conn,"pass","Password",secure=True)
        email = askInp(conn,"inp","UserName")
    elif account == 2:
        #forgot password
        pass
    else:
        #disconnect()
        pass
