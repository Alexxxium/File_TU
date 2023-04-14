import sqlite3 as sq
import googletrans


with sq.connect("Languages.db") as con:
    cur = con.cursor()

    cur.execute("""CREATE TABLE IF NOT EXISTS langs (
    lang TEXT,
    key TEXT
    )""")

    langs = googletrans.LANGUAGES

    for i in langs:
        cur.execute(f'''
        INSERT INTO langs
        (lang, key) 
        VALUES
        ('{langs.get(i).title()}', '{i}')''')

    con.commit()
