extends Control

onready var retry_button = get_node("%RetryButton");
onready var menu_button = get_node("%MenuButton");

func _ready():
	retry_button.connect("pressed", self, "retry");
	menu_button.connect("pressed", self, "menu");
	
func retry():
	var _error = get_tree().reload_current_scene();
	
func menu():
	var _error = get_tree().change_scene("res://scenes/levels/level_main_menu.tscn");
