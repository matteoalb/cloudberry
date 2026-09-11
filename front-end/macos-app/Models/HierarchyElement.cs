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
    public string path;
    private Dictionary<string, HierarchyElement> children;
    public HierarchyElement? parent;

    public HierarchyElement(string _name, int _depth, string _path, HierarchyElement? _parent)
    {
        name = _name;
        depth = _depth;
        path = _path;
        type = HierarchyLoad.GetTypeByName(_name);
        children = new Dictionary<string, HierarchyElement>();
        parent = _parent;
    }

    public List<HierarchyElement> GetChildren()
    {
        if(children.Count == 0)
            return new List<HierarchyElement>();

        return new List<HierarchyElement>(children.Values);
    }

    public List<HierarchyElement> GetImageChildren()
    {
        List<HierarchyElement> lst = new List<HierarchyElement>();

        foreach(HierarchyElement child in children.Values)
        {
            if(child.type == Type.Image)
                lst.Add(child);
        }

        return lst;
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

    public HierarchyElement GetChild(string n)
    {
        if (!children.ContainsKey(n))
        {
            Console.WriteLine("Unable to find child " + n + " of " + name + ", returned the parent.");
            return this;
        }

        return children[n];
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