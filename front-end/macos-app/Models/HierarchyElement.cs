using System;
using System.Collections.Generic;

namespace macos_app.Models;

public enum Type
{
    Folder,
    Image,
    Other
}

public class HierarchyElement
{
    public string name;
    public Type type;
    public int depth;
    private Dictionary<string, HierarchyElement> children;

    public HierarchyElement(string _name, int _depth)
    {
        name = _name;
        depth = _depth;
        type = HierarchyLoad.GetTypeByName(_name);
        children = new Dictionary<string, HierarchyElement>();
    }

    public List<HierarchyElement> GetChildren()
    {
        if(children.Count == 0)
            return new List<HierarchyElement>();

        return new List<HierarchyElement>(children.Values);
    }

    public void AddChild(HierarchyElement child)
    {
        if (children.ContainsKey(child.name))
        {
            Console.WriteLine("Tried to add existing child, returned.");
            return;
        }

        children.Add(child.name, child);
    }

    public override string ToString()
    {
        if(type != Type.Folder)
        {
            return "<" + name + "/>";
        }

        string s = "<" + name + ">";

        foreach(HierarchyElement child in children.Values)
        {
            s+=child.ToString();
        }

        s+="</" + name +">";

        return s;
    }
}