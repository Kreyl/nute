using System;
using System.Collections.Generic;
using System.Linq;
using HonorInterfaces;
using HonorLogic.ShipStatus;
using Newtonsoft.Json;

namespace HonorLogic.Storage
{
    [Serializable]
    public struct ShipStoredData
    {
        public Guid Id { get; set; }
        public string Name { get; set; }
        public List<ShipSubsystemStatus> Subsystems { get; set; }
        public List<int> Gates { get; set; }
        public List<byte> Rooms { get; set; }
    }

    internal class ShipStorage
    {
        private readonly StorageBase<ShipStoredData> _storageBase;
        private readonly Dictionary<Guid, ShipStoredData> _savedData;

        public ShipStorage()
        {
            _storageBase = new StorageBase<ShipStoredData>("ship");
            var readJson = _storageBase.ReadJson();
            if (readJson != null)
            {
                _savedData =
                    JsonConvert.DeserializeObject<List<ShipStoredData>>(readJson)
                        .ToDictionary(a => a.Id);
            }
            else
            {
                _savedData = new Dictionary<Guid, ShipStoredData>();
            }
        }

        public void SaveData(List<ShipStoredData> pairs)
        {
            _storageBase.Save(pairs);
        }

        public IShip CreateObject(Guid id, GlobalModel model)
        {
            var obj = _savedData.ContainsKey(id) ? (ShipStoredData?) _savedData[id] : null;
            var gates = obj == null ? new List<int> {71} : obj.Value.Gates;
            var big = gates.Count > 1;
            var ship = big ? (IShip) new BigShip() : new LakShip();
            ship.PhysicalGateID = gates.ToArray();
            if (obj != null)
            {
                foreach (var s in obj.Value.Subsystems)
                {
                    ship.SetSubsystemStatus(s);
                }
            }
            ship.Name = obj == null ? id.ToString() : obj.Value.Name;
            ship.Model = model;
            ship.ShipGuid = id;
            ship.ShipRoomsIDs = obj == null ? new List<byte>() : obj.Value.Rooms;
            return ship;
        }

        public IEnumerable<Guid> Keys
        {
            get { return _savedData.Keys.ToArray(); }
        }
    }
}