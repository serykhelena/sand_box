import json 

'''
Программа, которая эмулирует работу с пространствами имен

На вход подаются следующие запросы:

- create <namespace> <parent> –  создать новое пространство имен с именем <namespace> внутри пространства <parent>
- add <namespace> <var> – добавить в пространство <namespace> переменную <var>
- get <namespace> <var> – получить имя пространства, из которого будет взята переменная <var> при запросе из пространства <namespace>, или None, если такого пространства не существует

Более формально, результатом работы get <namespace> <var> является:

<namespace>, если в пространстве <namespace> была объявлена переменная <var>
get <parent> <var> – результат запроса к пространству, внутри которого было создано пространство <namespace>, если переменная не была объявлена
None, если не существует <parent>, т. е. <namespace>﻿ – это global

'''

namesp = dict()

namesp['global'] = {
	'parent' : None, 
	'vars' : set()
}

def set_default( obj ):
	if isinstance( obj, set ):
		return list(obj)

def find_item( obj, key ):
	count = 0
	if key in obj:
		return obj[key]
	if len( obj.keys() ) < 4:
		for k, v in obj.items():
			if isinstance(v,dict):
				return find_item( v, key )
	else: 
		for k, v in obj.items():
			if isinstance(v,dict):
				if find_item( v, key ) is None:
					continue
				else:
					return find_item( v, key )
	
	return None

def add( obj, namespace, var ):
	if namespace in obj:
		obj[namespace]['vars'].add(var)
	else:
		if find_item( obj, namespace ) is not None:
			find_item( obj, namespace )['vars'].add(var)
		else:
			print('WTF ADD')


def create( obj, namespace, parent ):
	if parent in obj:
		obj[parent][namespace] = {
			'parent' : parent, 
			'vars' : set()
		}
	else:
		if find_item( obj, parent ) is not None:
			find_item(obj, parent)[namespace] = {
					'parent' : parent, 
					'vars' : set()
			}
		else:
			print('WTF CREATE')


def get( obj, namespace, var ):
	if namespace in obj:
		if var in obj[namespace]['vars']:
			return namespace
	else:
		if find_item( obj, namespace ) is not None:
			if var in find_item( obj, namespace )['vars']:
				return namespace
			else:
				namespace = find_item( obj, namespace )['parent']
				return get( obj, namespace, var)

with open('task.txt') as file:
	for line in file:
		cmd, nsp, var = line.split()

		if cmd == 'add':
			print( cmd, nsp, var )
			add( namesp, nsp, var )
		elif cmd == 'create':
			print(f'{cmd} {nsp} {var}')
			create( namesp, nsp, var )
		elif cmd == 'get':
			print( cmd, nsp, var )
			print( get( namesp, nsp, var ) )

print( json.dumps( namesp, sort_keys=True, indent=4, default=set_default ) )












