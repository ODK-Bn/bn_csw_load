private ["_gun","_player","_mags_allowed","_load_time","_max_load","_mags_available","_timeout"];
_gun = _this select 0;
_player = _this select 1;
_mags_allowed = getArray (configFile >> "CfgWeapons" >> weapons _gun select 0 >> "magazines");
_load_time = getNumber (configFile >> "CfgWeapons" >> weapons _gun select 0 >> "bn_csw_ReloadTime");
_max_load = getNumber (configFile >> "CfgWeapons" >> weapons _gun select 0 >> "bn_csw_extra_capacity") + 1;
_mags_available = [];

/* if (!(local _gun)) then  {	
	bn_csw_give_owner = [_player, _gun];
	publicVariableServer "bn_csw_give_owner";
	_timeout = time;
	waitUntil {sleep 0.1; (local _gun) || (time > _timeout + 10);};
};
if (!(local _gun)) exitWith {hint "Не удалось решить проблему локальности"}; */

if ({_x in (magazines _player)} count _mags_allowed > 0) then {
	if (({(_x select 1) > 0} count magazinesAmmoFull _gun) >= _max_load) exitWith {hint "Уже заряжено!";};
	if ((_gun getVariable ["bn_csw_occupied",false]) || !(isNull (gunner _gun))) exitWith {hint "Орудие занято!"};
	{
		if ((_x select 0) in _mags_allowed) then {
			_mags_available=_mags_available+[_x];
		};
	} forEach magazinesAmmo _player;
//	hint (str _mags_available);
	_le_mag = _mags_available select 0;
	_player playAction "Gear";
	_gun setVariable ["bn_csw_occupied",true,true];
	[_load_time, [_player, _gun, _le_mag], "{
		[_this,'remoteLoad', _this select 1] call BIS_fnc_MP;		
		(_this select 0) removeMagazine ((_this select 2) select 0);
		(_this select 1) setVariable ['bn_csw_occupied',false,true];
		hint format ['Орудие %1 заряжено', getText (configFile >> 'CfgVehicles' >> typeOf (_this select 1) >> 'displayName')];

	}", "Заряжаю", "{_gun setVariable ['bn_csw_occupied',false,true]; hint 'Зарядка прервана'}"] call AGM_Core_fnc_progressBar;
} else {
	hint "Нет нужных боеприпасов!";
};

/* private ['_player', '_gun', '_le_mag', '_remember_mags', '_total_ammo','_mag_capacity','_full_mags','_leftovers'];
		_player = _this select 0;
		_gun = _this select 1;
		_le_mag = _this select 2;
		_remember_mags = magazinesAmmoFull (_gun);
		_total_ammo = (_le_mag) select 1;
		{
			_total_ammo = _total_ammo + (_x select 1);
		} forEach _remember_mags;
		(_gun) removeMagazinesTurret [(_le_mag) select 0, [0]];
		_mag_capacity = (getNumber (configFile >> 'CfgMagazines' >> (_le_mag) select 0 >> 'count'));
		_full_mags = floor (_total_ammo/_mag_capacity);
		_i = 0;
		for  '_i' from 1 to _full_mags do {(_gun) addMagazineTurret [(_le_mag) select 0,[0]]};
		_leftovers = _total_ammo % _mag_capacity;
		if (_leftovers>0) then {
			(_gun) addMagazineTurret [(_le_mag) select 0,[0]];
			(_gun) setAmmo [((weapons (_gun)) select 0), _leftovers];
		}; */