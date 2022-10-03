extends Node


func change_level(level_name: String):
	var actual_path: String = "res://scenes/levels/%s.tscn" % level_name;
	var _error = get_tree().change_scene(actual_path);
	
	
func restart_level():
	var _error = get_tree().reload_current_scene();
	
func quit():
	get_tree().quit();

