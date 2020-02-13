

import requests
import re

url='https://stepik.org/media/attachments/lesson/209719/2.html'

respons=requests.get(url).text.strip()

answer = re.findall(r'<code>(.*?)</code>',respons)

z={_:answer.count(_) for _ in answer}

[print(key,end=' ') for key,value in z.items() if value == z[max(z,key=z.get)] ]

