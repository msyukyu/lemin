from globals import *
from visu import Path

class BellmanFord:
	def __init__(self, rooms, s_room, e_room):
		self.rooms = rooms
		self.s_room = s_room
		self.e_room = e_room
		self.paths = BTree(None)
		self.start_path = None
		self.solve()

	def solve(self):
		for room in self.rooms:
			self.paths.add_data(Path(room, None))
		for i in range(len(self.rooms) - 1):
			self.__sub_solve(i)
		i = len(self.rooms) - 1
		if self.__sub_solve(i):
			print("error")
			return
		path = self.paths.get_data(self.e_room.name)
		if path is not None:
			reverse_path = Path(path.room, None)
			while path.previous is not None:
				path = path.previous
				reverse_path = Path(path.room, reverse_path)
			self.start_path = reverse_path

	def __sub_solve(self, i):
		changed = False
		room = self.rooms[i]
		path = self.paths.get_data(room.name)
		for jroom in room.get_joint_rooms():
			if jroom is self.s_room:
				continue
			tunnel = room.get_tunnel(jroom)
			jpath = self.paths.get_data(jroom.name)
			if jpath.previous is None or jpath.cost > tunnel.cost + path.cost:
				jpath.cost = tunnel.cost + path.cost
				jpath.previous = path
				changed = True
		return changed
